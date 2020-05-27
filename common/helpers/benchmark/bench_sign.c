/*
 * Copyright (c) 2020 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "KeccakP-1600-SnP.h"
#include "common/helpers/sign.h"

#ifdef KERL_SIMD_TIMES2
#include "SIMD128-config.h"
#elif KERL_SIMD_TIMES4
#include "SIMD256-config.h"
#endif

#ifdef KERL_TIMES2
#include "KeccakP-1600-times2-SnP.h"
#elif KERL_TIMES4
#include "KeccakP-1600-times4-SnP.h"
#elif KERL_TIMES8
#include "KeccakP-1600-times8-SnP.h"
#endif

#define NUM_OF_TIMES 100

tryte_t const *const SEED =
    (tryte_t *)"ABCDEFGHIJKLMNOPQRSTUVWXYZ9ABCDEFGHIJKLMNOPQRSTUVWXYZ9ABCDEFGHIJKLMNOPQRSTUVWXYZ9";

long diff_in_microsec(struct timeval start, struct timeval end) {
  long seconds = (end.tv_sec - start.tv_sec);
  return ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
}

void bench_gen_address(uint8_t security) {
  struct timeval start, end;
  long run_time = 0;
  long min = 0, max = 0, sum = 0;

  char *tmp_addr = NULL;
  for (int i = 0; i < NUM_OF_TIMES; i++) {
    gettimeofday(&start, NULL);
    tmp_addr = iota_sign_address_gen_trytes((char *)SEED, i, security);
    gettimeofday(&end, NULL);
    run_time = diff_in_microsec(start, end);
    max = (i == 0 || run_time > max) ? run_time : max;
    min = (i == 0 || run_time < min) ? run_time : min;
    sum += run_time;
    free(tmp_addr);
  }
  printf("security %d:\t%.3f\t%.3f\t%.3f\t%.3f\n", security, (min / 1000.0), (max / 1000.0),
         (sum / NUM_OF_TIMES) / 1000.0, sum / 1000.0);
}

void bench_gen_flex_address(uint8_t security) {
  struct timeval start, end;
  long run_time = 0;
  long min = 0, max = 0, sum = 0;
  flex_trit_t *tmp_addr = NULL;
  flex_trit_t flex_seed[FLEX_TRIT_SIZE_243];
  flex_trits_from_trytes(flex_seed, 243, SEED, 81, 81);

  for (int i = 0; i < NUM_OF_TIMES; i++) {
    gettimeofday(&start, NULL);
    tmp_addr = iota_sign_address_gen_flex_trits(flex_seed, i, security);
    gettimeofday(&end, NULL);
    run_time = diff_in_microsec(start, end);
    max = (i == 0 || run_time > max) ? run_time : max;
    min = (i == 0 || run_time < min) ? run_time : min;
    sum += run_time;
    free(tmp_addr);
  }
  printf("security %d:\t%.3f\t%.3f\t%.3f\t%.3f\n", security, (min / 1000.0), (max / 1000.0),
         (sum / NUM_OF_TIMES) / 1000.0, sum / 1000.0);
}

void bench_sign(uint8_t security) {
  struct timeval start, end;
  long run_time = 0;
  long min = 0, max = 0, sum = 0;

  char *tmp_signature = NULL;
  for (int i = 0; i < NUM_OF_TIMES; i++) {
    gettimeofday(&start, NULL);
    tmp_signature = iota_sign_signature_gen_trytes((char *)SEED, i, security, (char *)SEED);
    gettimeofday(&end, NULL);
    run_time = diff_in_microsec(start, end);
    max = (i == 0 || run_time > max) ? run_time : max;
    min = (i == 0 || run_time < min) ? run_time : min;
    sum += run_time;
    free(tmp_signature);
  }
  printf("security %d:\t%.3f\t%.3f\t%.3f\t%.3f\n", security, (min / 1000.0), (max / 1000.0),
         (sum / NUM_OF_TIMES) / 1000.0, sum / 1000.0);
}

int main(void) {
  printf("Kerl: %s", KeccakP1600_implementation);
#if KERL_SIMD_TIMES2
  printf(", %s\n", KeccakP1600times2_implementation_config);
#elif KERL_SIMD_TIMES4
  printf(", %s\n", KeccakP1600times4_implementation_config);
#elif KERL_TIMES2
  printf(", %s\n", KeccakP1600times2_implementation);
#elif KERL_TIMES4
  printf(", %s\n", KeccakP1600times4_implementation);
#elif KERL_TIMES8
  printf(", %s\n", KeccakP1600times8_implementation);
#else
  printf("\n");
#endif

  printf("Bench address generation: %d times\n\t\tmin(ms)\tmax(ms)\tavg(ms)\ttotal(ms)\n", NUM_OF_TIMES);
  bench_gen_address(1);
  bench_gen_address(2);
  bench_gen_address(3);

  printf("Bench flex address generation: %d times, %d trits per byte\n\t\tmin(ms)\tmax(ms)\tavg(ms)\ttotal(ms)\n",
         NUM_OF_TIMES, flex_trit_encoding());
  bench_gen_flex_address(1);
  bench_gen_address(2);
  bench_gen_address(3);

  printf("Bench signature signing: %d times\n\t\tmin(ms)\tmax(ms)\tavg(ms)\ttotal(ms)\n", NUM_OF_TIMES);
  bench_sign(1);
  bench_sign(2);
  bench_sign(3);

  return 0;
}
