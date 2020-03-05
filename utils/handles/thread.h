/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef __UTILS_HANDLES_THREAD_H__
#define __UTILS_HANDLES_THREAD_H__

#ifdef _WIN32
#include "utils/windows.h"
#else
#include <unistd.h>
#endif

#ifdef _POSIX_THREADS
#include <pthread.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * We define a type thread_handle_t mapping to a system available thread
 * primitive and its associated functions, some of them might have no effect if
 * not needed by the underlying API
 */

#ifdef _POSIX_THREADS
typedef pthread_t thread_handle_t;
#elif _WIN32
typedef HANDLE thread_handle_t;
#else
typedef int thread_handle_t;
#endif

typedef void *(*thread_routine_t)(void *);

/**
 * Creates a new thread
 *
 * @param[in] thread The thread
 * @param[in] routine The routine to launch
 * @param[in] arg Argument to give to the routine
 *
 * @return exit status
 */
static inline int thread_handle_create(thread_handle_t *const thread, thread_routine_t routine, void *arg) {
#ifdef _POSIX_THREADS
  return pthread_create(thread, NULL, routine, arg);
#elif _WIN32
  *thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)routine, arg, 0, NULL);
  return 0;
#else
  return 0;
#endif
}

/**
 * Waits for a thread termination
 *
 * @param[in] thread The thread
 * @param[in] status Exit status of the thread
 *
 * @return exit status
 */
static inline int thread_handle_join(thread_handle_t thread, void **status) {
#ifdef _POSIX_THREADS
  return pthread_join(thread, status);
#elif _WIN32
  WaitForSingleObject(thread, INFINITE);

  if (status) {
    *status = NULL;
    return !GetExitCodeThread(thread, (LPDWORD)status);
  }
  return 0;
#else
  return 0;
#endif
}

#ifdef __cplusplus
}
#endif

#endif  // __UTILS_HANDLES_THREAD_H__
