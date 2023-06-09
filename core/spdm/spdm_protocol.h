// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#ifndef SPDM_PROTOCOL_H_
#define SPDM_PROTOCOL_H_

#include <stdint.h>
#include "mctp/mctp_base_protocol.h"


#define SPDM_PROTOCOL_MIN_MSG_LEN							(sizeof (struct spdm_protocol_header))
#define SPDM_PROTOCOL_MAX_PAYLOAD_PER_MSG					(MCTP_BASE_PROTOCOL_MAX_MESSAGE_BODY - SPDM_PROTOCOL_MIN_MSG_LEN)

#define SPDM_NONCE_LEN										32

#define SPDM_MAJOR_VERSION									1
#define SPDM_MIN_MINOR_VERSION								1
#define SPDM_MAX_MINOR_VERSION								2

#define SPDM_MAX_RESPONSE_TIMEOUT_MS						100


#pragma pack(push, 1)
/**
 * SPDM portion of packet header
 */
struct spdm_protocol_header {
	uint8_t msg_type:7;										/**< MCTP message type */
	uint8_t integrity_check:1;								/**< MCTP message integrity check */
	uint8_t spdm_minor_version:4;							/**< SPDM specification minor version */
	uint8_t spdm_major_version:4;							/**< SPDM specification major version */
	uint8_t req_rsp_code;									/**< Request/Response message code */
};
#pragma pack(pop)

/**
 * SPDM protocol request/response codes
 */
enum {
	SPDM_RESPONSE_GET_DIGESTS = 0x01,               		/**< Response with certificate chain digests */
	SPDM_RESPONSE_GET_CERTIFICATE = 0x02,           		/**< Response with certificate chains */
	SPDM_RESPONSE_CHALLENGE = 0x03,           				/**< Challenge-response protocol response */
	SPDM_RESPONSE_GET_VERSION = 0x04,           			/**< SPDM specification version of device */
	SPDM_RESPONSE_GET_MEASUREMENTS = 0x60,           		/**< Response with easurements from device */
	SPDM_RESPONSE_GET_CAPABILITIES = 0x61,           		/**< SPDM capabilities of device */
	SPDM_RESPONSE_NEGOTIATE_ALGORITHMS = 0x63,           	/**< Negotiate cryptographic algorithms */
	SPDM_RESPONSE_KEY_EXCHANGE = 0x64,           			/**< Response for a initiate key exchange session establishment flow request */
	SPDM_RESPONSE_FINISH = 0x65,           					/**< Response for a complete key exchange session establishment flow request */
	SPDM_RESPONSE_PSK_EXCHANGE = 0x66,           			/**< Response for a initiate pre-shared key session establishment flow request */
	SPDM_RESPONSE_PSK_FINISH = 0x67,          				/**< Response for a complete pre-shared key session establishment request */
	SPDM_RESPONSE_HEARTBEAT = 0x68,           				/**< Keep session alive response */
	SPDM_RESPONSE_KEY_UPDATE = 0x69,           				/**< Update session keys response */
	SPDM_RESPONSE_GET_ENCAPSULATED_REQUEST = 0x6a,          /**< Response with request from device */
	SPDM_RESPONSE_DELIVER_ENCAPSULATED_RESPONSE = 0x6b,     /**< Response to response sent to device */
	SPDM_RESPONSE_END_SESSION = 0x6c,           			/**< Terminate session response */
	SPDM_RESPONSE_VENDOR_DEFINED_REQUEST = 0x7e,           	/**< Unique vendor defined response */
	SPDM_RESPONSE_ERROR = 0x7f,								/**< Error response message */
	SPDM_REQUEST_GET_DIGESTS = 0x81,               			/**< Retrieve certificate chain digests */
	SPDM_REQUEST_GET_CERTIFICATE = 0x82,           			/**< Retrieve certificate chains */
	SPDM_REQUEST_CHALLENGE = 0x83,           				/**< Authenticate device using challenge-response protocol */
	SPDM_REQUEST_GET_VERSION = 0x84,           				/**< Get SPDM specification version of device */
	SPDM_REQUEST_GET_MEASUREMENTS = 0xe0,           		/**< Retrieve measurements from device */
	SPDM_REQUEST_GET_CAPABILITIES = 0xe1,           		/**< Get SPDM capabilities of device */
	SPDM_REQUEST_NEGOTIATE_ALGORITHMS = 0xe3,           	/**< Negotiate cryptographic algorithms */
	SPDM_REQUEST_KEY_EXCHANGE = 0xe4,           			/**< Initiate key exchange session establishment flow */
	SPDM_REQUEST_FINISH = 0xe5,           					/**< Complete key exchange session establishment flow */
	SPDM_REQUEST_PSK_EXCHANGE = 0xe6,           			/**< Initiate pre-shared key session establishment flow */
	SPDM_REQUEST_PSK_FINISH = 0xe7,          				/**< Complete pre-shared key session establishment */
	SPDM_REQUEST_HEARTBEAT = 0xe8,           				/**< Keep session alive */
	SPDM_REQUEST_KEY_UPDATE = 0xe9,           				/**< Update session keys */
	SPDM_REQUEST_GET_ENCAPSULATED_REQUEST = 0xea,           /**< Get request from device */
	SPDM_REQUEST_DELIVER_ENCAPSULATED_RESPONSE = 0xeb,      /**< Send back response to device */
	SPDM_REQUEST_END_SESSION = 0xec,           				/**< Terminate session */
	SPDM_REQUEST_VENDOR_DEFINED_REQUEST = 0xfe,           	/**< Unique vendor defined request */
	SPDM_REQUEST_RESPOND_IF_READY = 0xff,          			/**< Request response from device */
};


#endif // SPDM_PROTOCOL_H_
