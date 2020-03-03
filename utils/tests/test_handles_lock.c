/*
 * Copyright (c) 2020 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#include <stdlib.h>
#include <unity/unity.h>

#include "utils/handles/lock.h"
#include "utils/handles/thread.h"

int g_counter;
static lock_handle_t lock;

static void dummy_loop_lock() {
  unsigned long i = 0;
  lock_handle_lock(&lock);
  g_counter += 1;
  printf("\n Job %d started\n", g_counter);
  for (i = 0; i < (0xFFFFFF); i++)
    ;
  printf("\n Job %d finished\n", g_counter);
  lock_handle_unlock(&lock);
}

void test_lock() {
  int thread_num = 5;
  thread_handle_t *threads = (thread_handle_t *)malloc(sizeof(thread_handle_t) * thread_num);
  lock_handle_init(&lock);
  g_counter = 0;

  for (int i = 0; i < thread_num; i++) {
    thread_handle_create(&threads[i], (thread_routine_t)dummy_loop_lock, NULL);
  }

  for (int i = 0; i < thread_num; i++) {
    thread_handle_join(threads[i], NULL);
  }

  lock_handle_destroy(&lock);
  free(threads);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_lock);

  return UNITY_END();
}
