/*
 * Copyright (c) 2020 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#include "common/trinary/trits.h"

bool is_trits(trit_t const *const trits, size_t len) {
  for (size_t i = 0; i < len; i++) {
    if (trits[i] < -1 || trits[i] > 1) {
      return false;
    }
  }
  return true;
}
