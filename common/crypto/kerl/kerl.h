/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef __COMMON_CRYPTO_KERL_KERL_H__
#define __COMMON_CRYPTO_KERL_KERL_H__

#include "FIPS202/KeccakHash.h"

#include "common/stdint.h"
#include "common/trinary/trits.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  Keccak_HashInstance keccak;
} Kerl;

void kerl_init(Kerl* const ctx);
void kerl_absorb(Kerl* const ctx, trit_t const* trits, size_t const length);
void kerl_squeeze(Kerl* const ctx, trit_t* trits, size_t const length);
void kerl_reset(Kerl* const ctx);

#ifdef __cplusplus
}
#endif

#endif  // __COMMON_CRYPTO_KERL_KERL_H__
