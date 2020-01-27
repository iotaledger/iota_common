/*
 * Copyright (c) 2020 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#include <stdio.h>
#include <unity/unity.h>

#include "common/trinary/trits.h"

void test_is_trits(void) {
  const trit_t tryte_LUT[27][3] = {
      {0, 0, 0},  {1, 0, 0},  {-1, 1, 0},  {0, 1, 0},  {1, 1, 0},  {-1, -1, 1},  {0, -1, 1},  {1, -1, 1},  {-1, 0, 1},
      {0, 0, 1},  {1, 0, 1},  {-1, 1, 1},  {0, 1, 1},  {1, 1, 1},  {-1, -1, -1}, {0, -1, -1}, {1, -1, -1}, {-1, 0, -1},
      {0, 0, -1}, {1, 0, -1}, {-1, 1, -1}, {0, 1, -1}, {1, 1, -1}, {-1, -1, 0},  {0, -1, 0},  {1, -1, 0},  {-1, 0, 0}};

  for (size_t i = 0; i < 27; i++) {
    printf("tryte LUT checking %ld\n", i);
    TEST_ASSERT(is_trits(tryte_LUT[i], 3) == true);
  }

  const trit_t ng_tryte[6][3] = {{2, 0, 0}, {1, 3, 0}, {-1, 1, 4}, {-2, 1, 0}, {1, -3, 0}, {-1, -1, -4}};
  for (size_t i = 0; i < 6; i++) {
    printf("ng_tryte checking %ld\n", i);
    TEST_ASSERT(is_trits(ng_tryte[i], 3) == false);
  }

  const trit_t trytes_LUT[14][6] = {{0, 0, 0, 1, 0, 0},   {-1, 1, 0, 0, 1, 0},     {1, 1, 0, -1, -1, 1},
                                    {0, -1, 1, 1, -1, 1}, {-1, 0, 1, 0, 0, 1},     {1, 0, 1, -1, 1, 1},
                                    {0, 1, 1, 1, 1, 1},   {-1, -1, -1, 0, -1, -1}, {1, -1, -1, -1, 0, -1},
                                    {0, 0, -1, 1, 0, -1}, {-1, 1, -1, 0, 1, -1},   {1, 1, -1, -1, -1, 0},
                                    {0, -1, 0, 1, -1, 0}, {-1, 0, 0, 1, 1, 1}};
  for (size_t i = 0; i < 14; i++) {
    printf("trytes LUT checking %ld\n", i);
    TEST_ASSERT(is_trits(trytes_LUT[i], 6) == true);
  }

  const trit_t ng_trytes[14][6] = {{2, 0, 0, 1, 0, 0},    {-1, 3, 0, 0, 1, 0},     {1, 1, 4, -1, -1, 1},
                                   {0, -1, 1, 5, -1, 1},  {-1, 0, 1, 0, 6, 1},     {1, 0, 1, -1, 1, 7},
                                   {-2, 1, 1, 1, 1, 1},   {-1, -3, -1, 0, -1, -1}, {1, -1, -4, -1, 0, -1},
                                   {0, 0, -1, -5, 0, -1}, {-1, 1, -1, 0, -6, -1},  {1, 1, -1, -1, -1, -7},
                                   {0, -1, 0, 1, -10, 0}, {-1, 10, 0, 1, 1, 1}};
  for (size_t i = 0; i < 14; i++) {
    printf("ng_trytes LUT checking %ld\n", i);
    TEST_ASSERT(is_trits(ng_trytes[i], 6) == false);
  }
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_is_trits);

  return UNITY_END();
}
