// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "cmd_interface.h"
#include "cerberus_protocol.h"
#include "cerberus_protocol_required_commands.h"
#include "cmd_interface_ac_rot.h"


static int cmd_interface_ac_rot_process_request (struct cmd_interface *intf,
	struct cmd_interface_msg *request)
{
	struct cmd_interface_ac_rot *slave = (struct cmd_interface_ac_rot*) intf;
	uint8_t command_id;
	uint8_t command_set;
	int status;

	status = cmd_interface_process_cerberus_protocol_message (&slave->base, request, &command_id,
		&command_set, true, true);
	if (status != 0) {
		return status;
	}

	switch (command_id) {
		case CERBERUS_PROTOCOL_GET_FW_VERSION:
			status = cerberus_protocol_get_fw_version (slave->fw_version, request);
			break;

		case CERBERUS_PROTOCOL_GET_DIGEST:
			status = cerberus_protocol_get_certificate_digest (slave->attestation,
				slave->base.session, request);
			break;

		case CERBERUS_PROTOCOL_GET_CERTIFICATE:
			status = cerberus_protocol_get_certificate (slave->attestation, request);
			break;

		case CERBERUS_PROTOCOL_ATTESTATION_CHALLENGE:
			status = cerberus_protocol_get_challenge_response (slave->attestation,
				slave->base.session, request);
			break;

		case CERBERUS_PROTOCOL_GET_DEVICE_CAPABILITIES:
			status = cerberus_protocol_get_device_capabilities (slave->device_manager,
				request);
			break;

		case CERBERUS_PROTOCOL_EXPORT_CSR:
			status = cerberus_protocol_export_csr (slave->riot, request);
			break;

		case CERBERUS_PROTOCOL_IMPORT_CA_SIGNED_CERT:
			status = cerberus_protocol_import_ca_signed_cert (slave->riot,
				slave->background, request);
			break;

		case CERBERUS_PROTOCOL_GET_SIGNED_CERT_STATE:
			status = cerberus_protocol_get_signed_cert_state (slave->background, request);
			break;

		case CERBERUS_PROTOCOL_GET_DEVICE_INFO:
			status = cerberus_protocol_get_device_info (slave->cmd_device, request);
			break;

		case CERBERUS_PROTOCOL_GET_DEVICE_ID:
			status = cerberus_protocol_get_device_id (&slave->device_id, request);
			break;

		case CERBERUS_PROTOCOL_RESET_COUNTER:
			status = cerberus_protocol_reset_counter (slave->cmd_device, request);
			break;

#ifdef CMD_SUPPORT_ENCRYPTED_SESSIONS
		case CERBERUS_PROTOCOL_EXCHANGE_KEYS:
			status = cerberus_protocol_key_exchange (slave->base.session, request,
				intf->curr_txn_encrypted);
			break;

		case CERBERUS_PROTOCOL_SESSION_SYNC:
			status = cerberus_protocol_session_sync (slave->base.session, request,
				intf->curr_txn_encrypted);
			break;
#endif

		default:
			return CMD_HANDLER_UNKNOWN_REQUEST;
	}

	if (status == 0) {
		status = cmd_interface_prepare_response (&slave->base, request);
	}

	return status;
}

#ifdef CMD_ENABLE_ISSUE_REQUEST
static int cmd_interface_ac_rot_process_response (struct cmd_interface *intf,
	struct cmd_interface_msg *response)
{
	return CMD_HANDLER_UNSUPPORTED_OPERATION;
}
#endif

/**
 * Initialize System command interface instance
 *
 * @param intf The System command interface instance to initialize
 * @param attestation Attestation responder instance to utilize
 * @param device_manager Device manager
 * @param background Context for executing long-running operations in the background.
 * @param fw_version The FW version strings
 * @param riot RIoT keys manager
 * @param cmd_device Device command handler instance
 * @param vendor_id Device vendor ID
 * @param device_id Device ID
 * @param subsystem_vid Subsystem vendor ID
 * @param subsystem_id Subsystem ID
 * @param session Session manager for channel encryption
 *
 * @return Initialization status, 0 if success or an error code.
 */
int cmd_interface_ac_rot_init (struct cmd_interface_ac_rot *intf,
	struct attestation_responder *attestation, struct device_manager *device_manager,
	struct cmd_background *background, struct cmd_interface_fw_version *fw_version,
	struct riot_key_manager *riot, struct cmd_device *cmd_device, uint16_t vendor_id,
	uint16_t device_id, uint16_t subsystem_vid, uint16_t subsystem_id,
	struct session_manager *session)
{
	if ((intf == NULL) || (background == NULL) || (riot == NULL) || (attestation == NULL) ||
		(device_manager == NULL) || (fw_version == NULL) || (cmd_device == NULL)) {
		return CMD_HANDLER_INVALID_ARGUMENT;
	}

	memset (intf, 0, sizeof (struct cmd_interface_ac_rot));

	intf->riot = riot;
	intf->background = background;
	intf->attestation = attestation;
	intf->device_manager = device_manager;
	intf->fw_version = fw_version;
	intf->cmd_device = cmd_device;

	intf->device_id.vendor_id = vendor_id;
	intf->device_id.device_id = device_id;
	intf->device_id.subsystem_vid = subsystem_vid;
	intf->device_id.subsystem_id = subsystem_id;

	intf->base.process_request = cmd_interface_ac_rot_process_request;
#ifdef CMD_ENABLE_ISSUE_REQUEST
	intf->base.process_response = cmd_interface_ac_rot_process_response;
#endif
	intf->base.generate_error_packet = cmd_interface_generate_error_packet;

#ifdef CMD_SUPPORT_ENCRYPTED_SESSIONS
	intf->base.session = session;
#endif

	return 0;
}

/**
 * Deinitialize slave system command interface instance
 *
 * @param intf The slave system command interface instance to deinitialize
 */
void cmd_interface_ac_rot_deinit (struct cmd_interface_ac_rot *intf)
{
	if (intf != NULL) {
		memset (intf, 0, sizeof (struct cmd_interface_ac_rot));
	}
}
