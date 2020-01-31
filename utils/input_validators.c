/*
 * Copyright (c) 2020 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#include "utils/input_validators.h"
#include "common/model/transaction.h"

bool is_tryte_with_trailing_zero(tryte_t const tryte) {
  if (tryte == '9' || (tryte >= 'A' && tryte <= 'D') || (tryte >= 'W' && tryte <= 'Z')) {
    return true;
  }
  return false;
}

bool is_address(tryte_t const *const address) {
  if (is_trytes(address, NUM_TRYTES_ADDRESS)) {
    return is_tryte_with_trailing_zero(address[NUM_TRYTES_ADDRESS - 1]);
  }
  return false;
}

bool is_address_with_checksum(tryte_t const *const address) {
  if (is_trytes(address, NUM_TRYTES_ADDRESS + NUM_TRYTES_CHECKSUM)) {
    return is_tryte_with_trailing_zero(address[NUM_TRYTES_ADDRESS - 1]);
  }
  return false;
}

bool is_tag(tryte_t const *const tag) { return is_trytes(tag, NUM_TRYTES_TAG); }

bool is_seed(tryte_t const *const seed) { return is_trytes(seed, NUM_TRYTES_HASH); }

bool is_security_level(uint8_t level) { return (level >= 1 && level <= 3); }
