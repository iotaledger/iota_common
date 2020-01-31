/*
 * Copyright (c) 2020 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#include <unity/unity.h>

#include "utils/input_validators.h"

void test_is_tryte_with_trailing_zero() {
  TEST_ASSERT(is_tryte_with_trailing_zero('9') == true);
  TEST_ASSERT(is_tryte_with_trailing_zero('A') == true);
  TEST_ASSERT(is_tryte_with_trailing_zero('B') == true);
  TEST_ASSERT(is_tryte_with_trailing_zero('C') == true);
  TEST_ASSERT(is_tryte_with_trailing_zero('D') == true);
  TEST_ASSERT(is_tryte_with_trailing_zero('E') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('F') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('G') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('H') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('I') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('J') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('K') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('L') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('M') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('N') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('O') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('P') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('Q') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('R') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('S') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('T') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('U') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('V') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('W') == true);
  TEST_ASSERT(is_tryte_with_trailing_zero('X') == true);
  TEST_ASSERT(is_tryte_with_trailing_zero('Y') == true);
  TEST_ASSERT(is_tryte_with_trailing_zero('Z') == true);

  TEST_ASSERT(is_tryte_with_trailing_zero('2') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('a') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('b') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('c') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('d') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('e') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('f') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('g') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('h') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('i') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('j') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('k') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('l') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('m') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('n') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('o') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('p') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('q') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('r') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('s') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('t') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('u') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('v') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('w') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('x') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('y') == false);
  TEST_ASSERT(is_tryte_with_trailing_zero('z') == false);
}

void test_is_address() {
  TEST_ASSERT(
      is_address((tryte_t *)"RJBYLCIOUKWJVCUKZQZCPIKNBUOGRGVXHRTTE9ZFSCGTFRKELMJBDDAKEYYCLHLJDNSHQ9RTIUIDLMUOB") ==
      true);

  // invalid trytes
  TEST_ASSERT(
      is_address((tryte_t *)"0JBYLCIOUKWJVCUKZQZCPIKNBUOGRGVXHRTTE9ZFSCGTFRKELMJBDDAKEYYCLHLJDNSHQ9RTIUIDLMUOB") ==
      false);

  // invalid length
  TEST_ASSERT(
      is_address((tryte_t *)"RJBYLCIOUKWJVCUKZQZCPIKNBUOGRGVXHRTTE9ZFSCGTFRKELMJBDDAKEYYCLHLJDNSHQ9RTIUIDLMUOBBBB") ==
      false);

  // invalid length
  TEST_ASSERT(is_address((tryte_t *)"IOUKWJVCUKZQZCPIKNBUOGRGVXHRTTE9ZFSCGTFRKELMJBDDAKEYYCLHLJDNSHQ9RTIUIDLMUOB") ==
              false);

  // without trailing zero
  TEST_ASSERT(
      is_address((tryte_t *)"SH9PTSGXVZULPFFBNDXFKEDVBBQMY9RTHTDELDEYPWBYBQUEFWBBJRPOBWMYLGJE9YGTDFBEJFKNYRKKK") ==
      false);
}

void test_is_address_with_checksum() {
  TEST_ASSERT(
      is_address_with_checksum(
          (tryte_t *)"RJBYLCIOUKWJVCUKZQZCPIKNBUOGRGVXHRTTE9ZFSCGTFRKELMJBDDAKEYYCLHLJDNSHQ9RTIUIDLMUOBVG9LXZ9PB") ==
      true);

  // invalid trytes
  TEST_ASSERT(
      is_address_with_checksum(
          (tryte_t *)"0JBYLCIOUKWJVCUKZQZCPIKNBUOGRGVXHRTTE9ZFSCGTFRKELMJBDDAKEYYCLHLJDNSHQ9RTIUIDLMUOBVG9LXZ9PB") ==
      false);

  // invalid length
  TEST_ASSERT(is_address_with_checksum(
                  (tryte_t *)"RJBYLCIOUKWJVCUKZQZCPIKNBUOGRGVXHRTTE9ZFSCGTFRKELMJBDDAKEYYCLHLJDNSHQ9RTIUIDLMUOB") ==
              false);

  // without trailing zero
  TEST_ASSERT(
      is_address_with_checksum(
          (tryte_t *)"SH9PTSGXVZULPFFBNDXFKEDVBBQMY9RTHTDELDEYPWBYBQUEFWBBJRPOBWMYLGJE9YGTDFBEJFKNYRKKKVG9LXZ9PB") ==
      false);
}

void test_is_security_level() {
  TEST_ASSERT(is_security_level(0) == false);
  TEST_ASSERT(is_security_level(1) == true);
  TEST_ASSERT(is_security_level(2) == true);
  TEST_ASSERT(is_security_level(3) == true);
  TEST_ASSERT(is_security_level(4) == false);
  TEST_ASSERT(is_security_level(5) == false);
  TEST_ASSERT(is_security_level(6) == false);
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_is_tryte_with_trailing_zero);
  RUN_TEST(test_is_address);
  RUN_TEST(test_is_address_with_checksum);
  RUN_TEST(test_is_security_level);

  return UNITY_END();
}
