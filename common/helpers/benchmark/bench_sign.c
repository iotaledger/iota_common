
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "common/helpers/sign.h"

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
  printf("security %d:\t%.3f\t%.3f\t%.3f\n", security, (min / 1000.0), (max / 1000.0), (sum / NUM_OF_TIMES) / 1000.0);
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
  printf("security %d:\t%.3f\t%.3f\t%.3f\n", security, (min / 1000.0), (max / 1000.0), (sum / NUM_OF_TIMES) / 1000.0);
}

int main(void) {
  printf("Bench address generation: %d times\n\t\tmin(ms)\tmax(ms)\tavg(ms)\n", NUM_OF_TIMES);
  bench_gen_address(1);
  bench_gen_address(2);
  bench_gen_address(3);

  printf("Bench signature signing: %d times\n\t\tmin(ms)\tmax(ms)\tavg(ms)\n", NUM_OF_TIMES);
  bench_sign(1);
  bench_sign(2);
  bench_sign(3);

  return 0;
}