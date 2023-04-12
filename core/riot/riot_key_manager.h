// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#ifndef RIOT_KEY_MANAGER_H_
#define RIOT_KEY_MANAGER_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "status/rot_status.h"
#include "platform_api.h"
#include "keystore/keystore.h"
#include "riot_keys.h"
#include "crypto/x509.h"
#include "common/certificate.h"


/**
 * Management of RIoT device keys.
 */
struct riot_key_manager {
	struct keystore *keystore;				/**< Storage for RIoT keys. */
	struct riot_keys keys;					/**< The keys generated by RIoT Core. */
	struct x509_engine *x509;				/**< X.509 engine for certificate authentication. */
	struct der_cert root_ca;				/**< The RIoT root CA certificate. */
	struct der_cert intermediate_ca;		/**< The RIoT intermediate CA certificate. */
	bool static_keys;						/**< Flag indicating static key buffers. */
	bool static_devid;						/**< Flag indicating a static device ID cert buffer. */
	platform_mutex store_lock;				/**< Synchronization for cert storage. */
	platform_mutex auth_lock;				/**< Synchronization for key updates. */
};


int riot_key_manager_init (struct riot_key_manager *riot, struct keystore *keystore,
	const struct riot_keys *keys, struct x509_engine *x509);
int riot_key_manager_init_static (struct riot_key_manager *riot, struct keystore *keystore,
	const struct riot_keys *keys, struct x509_engine *x509);
void riot_key_manager_release (struct riot_key_manager *keystore);

int riot_key_manager_store_signed_device_id (struct riot_key_manager *riot, const uint8_t *dev_id,
	size_t length);
int riot_key_manager_store_root_ca (struct riot_key_manager *riot, const uint8_t *root_ca,
	size_t length);
int riot_key_manager_store_intermediate_ca (struct riot_key_manager *riot, const uint8_t *intr_ca,
	size_t length);
int riot_key_manager_verify_stored_certs (struct riot_key_manager *riot);

int riot_key_manager_erase_all_certificates (struct riot_key_manager *riot);

const struct riot_keys* riot_key_manager_get_riot_keys (struct riot_key_manager *riot);
void riot_key_manager_release_riot_keys (struct riot_key_manager *riot,
	const struct riot_keys *keys);

const struct der_cert* riot_key_manager_get_root_ca (struct riot_key_manager *riot);
const struct der_cert* riot_key_manager_get_intermediate_ca (struct riot_key_manager *riot);


#define	RIOT_KEY_MANAGER_ERROR(code)		ROT_ERROR (ROT_MODULE_RIOT_KEY_MANAGER, code)

/**
 * Error codes that can be generated by a RIoT key manager.
 */
enum {
	RIOT_KEY_MANAGER_INVALID_ARGUMENT = RIOT_KEY_MANAGER_ERROR (0x00),		/**< Input parameter is null or not valid. */
	RIOT_KEY_MANAGER_NO_MEMORY = RIOT_KEY_MANAGER_ERROR (0x01),				/**< Memory allocation failed. */
	RIOT_KEY_MANAGER_KEYSTORE_LOCKED = RIOT_KEY_MANAGER_ERROR (0x02),		/**< The keystore is locked from modification. */
	RIOT_KEY_MANAGER_NO_SIGNED_DEVICE_ID = RIOT_KEY_MANAGER_ERROR (0x03),	/**< There is no signed device ID stored. */
	RIOT_KEY_MANAGER_NO_ROOT_CA = RIOT_KEY_MANAGER_ERROR (0x04),			/**< There is no root CA stored. */
};


#endif /* RIOT_KEY_MANAGER_H_ */
