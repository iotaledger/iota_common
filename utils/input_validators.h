/*
 * Copyright (c) 2020 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef __INPUT_VALIDATORS_H__
#define __INPUT_VALIDATORS_H__

#include <stdbool.h>
#include <stdlib.h>

#include "common/trinary/trits.h"
#include "common/trinary/tryte.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Checks if a tryte with a trailing zero trit.
 *
 * @param[in] tryte A tryte
 * @return boolean
 */
bool is_tryte_with_trailing_zero(tryte_t const tryte);

/**
 * @brief Checks if the given address is valid.
 *
 * An address should be 81 trytes with a zero-trit at tail.
 *
 * @param[in] address A hash string.
 * @return boolean
 */
bool is_address(tryte_t const* const address);

/**
 * @brief Checks if address hash contains checksum
 *
 * It won't validate checksum, checks the hash length only.
 *
 * @param[in] address A hash string.
 * @return boolean
 */
bool is_address_with_checksum(tryte_t const* const address);

/**
 * @brief Checks if the given hash is a tag.
 *
 * @param[in] tag A hash string.
 * @return boolean
 */
bool is_tag(tryte_t const* const tag);

/**
 * @brief Checks if the given hash is a seed.
 *
 * @param[in] seed A hash string.
 * @return boolean
 */
bool is_seed(tryte_t const* const seed);

/**
 * @brief Checks if the given number is a security level.
 *
 * @param[in] level An integer.
 * @return boolean
 */
bool is_security_level(uint8_t level);

#ifdef __cplusplus
}
#endif

#endif  // __INPUT_VALIDATORS_H__
