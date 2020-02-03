/*
 * Copyright (c) 2020 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#include <string.h>

#include "common/trinary/tryte.h"

bool is_trytes(tryte_t const *const trytes, size_t len) {
  size_t trytes_cnt = strlen((char *)trytes);
  if (trytes_cnt != len) {
    // length does not match.
    return false;
  }

  for (size_t i = 0; i < len; i++) {
    if (trytes[i] != '9' && (trytes[i] < 'A' || trytes[i] > 'Z')) {
      return false;
    }
  }
  return true;
}
