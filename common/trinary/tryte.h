/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef __COMMON_TRINARY_TRYTE_H_
#define __COMMON_TRINARY_TRYTE_H_

#include <stdbool.h>

#include "common/stdint.h"

typedef int8_t tryte_t;

#define INDEX_OF_TRYTE(tryte) ((tryte) == '9' ? 0 : ((tryte) - 'A' + 1))

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Checks if given trytes are valid.
 *
 * @param[in] trytes A string of trytes.
 * @param[in] len The length of the string.
 * @return boolean
 */
bool is_trytes(tryte_t const *const trytes, size_t len);

#ifdef __cplusplus
}
#endif

#endif  // __COMMON_TRINARY_TRYTE_H_
