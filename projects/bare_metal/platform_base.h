// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#ifndef PLATFORM_BASE_H_
#define PLATFORM_BASE_H_

#include <stdlib.h>
#include <stdint.h>
#include "common/common_math.h"
#include "common/unused.h"


/* This file provides a basic set of platform abstractions for bare metal systems that don't
 * require any hardware knowledge. */

/* Use stdlib malloc/free. */
#define	platform_malloc		malloc
#define	platform_calloc		calloc
#define	platform_realloc	realloc
#define	platform_free		free


/* Use common byte swapping macros.  Assumes a little endian CPU. */
#define	platform_htonl		SWAP_BYTES_UINT32
#define platform_htons		SWAP_BYTES_UINT16


/* platform_clock and system time functions depend on hardware features. */


/* Mutex.  Single-threaded environment without a need for synchronization. */
typedef int platform_mutex;

static inline int platform_mutex_init (platform_mutex *mutex)
{
	UNUSED (mutex);
	return 0;
}

static inline int platform_mutex_free (platform_mutex *mutex)
{
	UNUSED (mutex);
	return 0;
}

static inline int platform_mutex_lock (platform_mutex *mutex)
{
	UNUSED (mutex);
	return 0;
}

static inline int platform_mutex_unlock (platform_mutex *mutex)
{
	UNUSED (mutex);
	return 0;
}

/* Recursive mutex. */
#define	platform_recursive_mutex_init		platform_mutex_init
#define	platform_recursive_mutex_free		platform_mutex_free
#define	platform_recursive_mutex_lock		platform_mutex_lock
#define	platform_recursive_mutex_unlock		platform_mutex_unlock


/* platform_timer depends on hardware features. */


/* Semaphore. */
typedef int platform_semaphore;


/* Error codes to use for bare metal platform API failures. */
#define	PLATFORM_INVALID_ARGUMENT		0
#define	PLATFORM_NO_MEMORY				1
#define	PLATFORM_FAILURE				2


#endif /* PLATFORM_BASE_H_ */
