/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#include <inttypes.h>
#include <unity/unity.h>

#include "common/crypto/iss/normalize.h"
#include "common/model/bundle.h"
#include "common/model/tests/defs.h"
#include "common/trinary/flex_trit.h"
#include "common/trinary/tryte_ascii.h"

static tryte_t *trytes =
    (tryte_t *)"AABCDEFGHIJKLMNOPQRSTUVWXYZ9ABCDEFGHIJKLMNOPQRSTUVWXYZ9ABCDEFGHIJKLMNOPQRS"
    "TUVWXYZ";

static byte_t bytes[] = {0,   1,   2,   3,  4,  5,   6,   7,   8,   9,  10, 11, 12, 13, -13, -12, -11, -10, -9, -8, -7,
                         -6,  -5,  -4,  -3, -2, -1,  0,   1,   2,   3,  4,  5,  6,  7,  8,   9,   10,  11,  12, 13, -13,
                         -12, -11, -10, -9, -8, -7,  -6,  -5,  -4,  -3, -2, -1, 0,  1,  2,   3,   4,   5,   6,  7,  8,
                         9,   10,  11,  12, 13, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4,  -3,  -2,  -1};

static char const *const long_message =
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla condimentum diam nisi, aliquam tempor risus ornare "
    "a. Phasellus dignissim orci eget sagittis ultricies. Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
    "Duis facilisis turpis eu sem egestas tempus. Pellentesque a efficitur dui. Nullam vulputate euismod enim, nec "
    "vehicula augue venenatis vel. Vivamus tempor mollis dui a sollicitudin. Duis egestas lorem id elit vulputate, sit "
    "amet commodo odio cursus. Donec ac dictum lacus, a varius turpis. Proin scelerisque magna vitae tempor facilisis. "
    "Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Etiam id dui "
    "ultricies ligula faucibus eleifend et sed dolor. Duis aliquet lectus justo, at sodales ex vehicula ac. Integer "
    "luctus nulla et est luctus, sit amet lobortis ante pharetra.Sed sit amet ex tristique, faucibus felis et, "
    "dignissim elit. Sed vitae mollis lacus. Proin nec rutrum arcu. Vestibulum nec velit ac risus rutrum aliquet vitae "
    "dignissim est. Praesent non ante vitae est ultricies tempus. Nullam erat tellus, eleifend ut rutrum eget, "
    "sagittis a tortor. Morbi iaculis blandit laoreet. Quisque non lectus id ex pharetra fringilla id vitae mi. Nunc "
    "pharetra sed sapien ac blandit. Sed vulputate risus eget magna vehicula, quis facilisis quam vestibulum.Donec "
    "odio risus, maximus non elit in, mollis pharetra mi. Quisque lobortis cursus pretium. Pellentesque ac bibendum "
    "sem. Integer non leo placerat, mollis ex sit amet, dapibus sed.";

static char const *const short_message = "Hello IOTA!!!";

void test_normalized_bundle(void) {
  size_t length = strlen((char *)trytes);
  byte_t normalized_bundle_bytes[length];
  flex_trit_t bundle_flex_trits[FLEX_TRIT_SIZE_243];

  flex_trits_from_trytes(bundle_flex_trits, HASH_LENGTH_TRIT, trytes, length, length);
  normalize_flex_hash(bundle_flex_trits, normalized_bundle_bytes);
  TEST_ASSERT_EQUAL_MEMORY(bytes, normalized_bundle_bytes, length);
}

static void test_bundle_message(char const *const message) {
  // applying message to a bundle
  bundle_transactions_t *bundle = NULL;
  bundle_transactions_new(&bundle);
  bundle_set_message_string(bundle, message);

  // extracting the message
  char *bundle_msg = bundle_get_message_string(bundle);
  TEST_ASSERT_EQUAL_MEMORY(message, bundle_msg, strlen((char *)message));

  free(bundle_msg);
  bundle_transactions_free(&bundle);
}

void test_bundle_transactions_message_short(void) { test_bundle_message(short_message); }

void test_bundle_transactions_message_long(void) { test_bundle_message(long_message); }

void test_bundle_finalize(void) {
  bundle_transactions_t *bundle = NULL;
  Kerl kerl;
  bundle_transactions_new(&bundle);
  kerl_init(&kerl);
  flex_trit_t flex_bundle_hash[FLEX_TRIT_SIZE_243];
  flex_trit_t flex_addr[FLEX_TRIT_SIZE_243];
  flex_trit_t flex_tag[FLEX_TRIT_SIZE_81];
  TEST_ASSERT(flex_trits_from_trytes(flex_bundle_hash, NUM_TRITS_HASH, TEST_FINALIZED_BUNDLE_HASH, NUM_TRYTES_HASH,
                                     NUM_TRYTES_HASH));
  TEST_ASSERT(
      flex_trits_from_trytes(flex_addr, NUM_TRITS_HASH, TEST_ADDRESS_0, NUM_TRYTES_ADDRESS, NUM_TRYTES_ADDRESS));
  TEST_ASSERT(flex_trits_from_trytes(flex_tag, NUM_TRITS_TAG, TEST_TAG, NUM_TRYTES_TAG, NUM_TRYTES_TAG));
  TEST_ASSERT_NOT_NULL(bundle);

  // create a transaction in a bundle
  iota_transaction_t tx;
  transaction_reset(&tx);
  transaction_set_address(&tx, flex_addr);
  transaction_set_tag(&tx, flex_tag);
  transaction_set_timestamp(&tx, TEST_TIMESTAMP);
  transaction_set_value(&tx, 0);
  transaction_set_obsolete_tag(&tx, flex_tag);
  bundle_transactions_add(bundle, &tx);

  // clean up and transaction index reordering
  bundle_reset_indexes(bundle);
  TEST_ASSERT(bundle_finalize(bundle, &kerl) == RC_OK);

  // validating the bundel hash
  iota_transaction_t *tx_obj = bundle_at(bundle, 0);
  TEST_ASSERT_NOT_NULL(tx_obj);
  TEST_ASSERT_EQUAL_MEMORY(transaction_bundle(tx_obj), flex_bundle_hash, FLEX_TRIT_SIZE_243);

  bundle_transactions_free(&bundle);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_normalized_bundle);
  RUN_TEST(test_bundle_transactions_message_long);
  RUN_TEST(test_bundle_transactions_message_short);
  RUN_TEST(test_bundle_finalize);

  return UNITY_END();
}
