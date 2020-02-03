/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef __COMMON_TRINARY_TRIT_H_
#define __COMMON_TRINARY_TRIT_H_

#include <stdbool.h>

#include "common/stdint.h"

typedef int8_t trit_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Checks if the given trits are valid.
 *
 * @param[in] trits A trits array.
 * @param[in] len The length of trits array.
 * @return boolean
 */
bool is_trits(trit_t const* const trits, size_t len);

#ifdef __cplusplus
}
#endif

#endif  // __COMMON_TRINARY_TRIT_H_
