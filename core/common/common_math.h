// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#ifndef COMMON_MATH_H_
#define COMMON_MATH_H_

#include <stdint.h>


/**
 * Determine the minimum of two numbers.
 */
#define	min(a, b)	(((a) < (b)) ? (a) : (b))

/**
 * Reverse the byte order for a 32-bit integer.
 */
#define	SWAP_BYTES_UINT32(x)	((((x) >> 24) & 0xff) | (((x) >> 8) & 0xff00) | (((x) & 0xff00) << 8) | (((x) & 0xff) << 24))

/**
 * Reverse the byte order for a 16-bit integer.
 */
#define	SWAP_BYTES_UINT16(x)	((((x) >> 8) & 0xff) | (((x) & 0xff) << 8))


int common_math_get_num_bits_set (uint8_t byte);
int common_math_get_num_bits_set_before_index (uint8_t byte, uint8_t index);


#endif //COMMON_MATH_H_
