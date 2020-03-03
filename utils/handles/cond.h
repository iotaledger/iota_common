/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef __UTILS_HANDLES_COND_H__
#define __UTILS_HANDLES_COND_H__

#include <stdint.h>
#ifdef _WIN32
#include "utils/windows.h"
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#ifdef _POSIX_THREADS
#include <pthread.h>
#endif

#include "utils/handles/lock.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * We define a type cond_handle_t mapping to a system available condition
 * variable primitive and its associated functions, some of them might have no
 * effect if not needed by the underlying API
 */

#ifdef _POSIX_THREADS
typedef pthread_cond_t cond_handle_t;
#elif _WIN32
typedef CONDITION_VARIABLE cond_handle_t;
#endif

/**
 * Initializes a condition variable object with the specified attributes for use
 *
 * @param[in] cond The condition variable
 *
 * @return exit status
 */
static inline int cond_handle_init(cond_handle_t* const cond) {
#ifdef _POSIX_THREADS
  return pthread_cond_init(cond, NULL);
#elif _WIN32
  InitializeConditionVariable(cond);
  return 0;
#else
  return 0;
#endif
}

/**
 * Wakes up at least one thread that is currently waiting on the condition
 * variable specified by cond
 *
 * @param[in] cond The condition variable
 *
 * @return exit status
 */
static inline int cond_handle_signal(cond_handle_t* const cond) {
#ifdef _POSIX_THREADS
  return pthread_cond_signal(cond);
#elif _WIN32
  WakeConditionVariable(cond);
  return 0;
#else
  return 0;
#endif
}

/**
 * Wakes up all threads that are currently waiting on the condition variable
 * specified by cond
 *
 * @param[in] cond The condition variable
 *
 * @return exit status
 */
static inline int cond_handle_broadcast(cond_handle_t* const cond) {
#ifdef _POSIX_THREADS
  return pthread_cond_broadcast(cond);
#elif _WIN32
  WakeAllConditionVariable(cond);
  return 0;
#else
  return 0;
#endif
}

/**
 * Blocks the calling thread, waiting for the condition specified by cond to be
 * signaled or broadcast to
 *
 * @param[in] cond The condition variable
 * @param[in] lock The associated lock
 *
 * @return exit status
 */
static inline int cond_handle_wait(cond_handle_t* const cond, lock_handle_t* const lock) {
#ifdef _POSIX_THREADS
  return pthread_cond_wait(cond, lock);
#elif _WIN32
  SleepConditionVariableCS(cond, lock, INFINITE);
  return 0;
#else
  return 0;
#endif
}

/**
 * Blocks the calling thread, waiting for the condition specified by cond to be
 * signaled or broadcast to, or until the timeout is reached
 *
 * @param[in] cond The condition variable
 * @param[in] lock The associated lock
 * @param[in] timeout The timeout in milliseconds
 *
 * @return exit status
 */
static inline int cond_handle_timedwait(cond_handle_t* const cond, lock_handle_t* const lock,
                                        uint64_t const timeout_ms) {
#ifdef _POSIX_THREADS
  struct timespec ts;
  struct timeval tv;

  gettimeofday(&tv, NULL);
  ts.tv_sec = tv.tv_sec + timeout_ms / 1000ULL;
  ts.tv_nsec = tv.tv_usec * 1000ULL + (timeout_ms % 1000ULL) * 1000000ULL;
  if (ts.tv_nsec >= 1000000000LL) {
    ts.tv_sec++;
    ts.tv_nsec -= 1000000000ULL;
  }

  return pthread_cond_timedwait(cond, lock, &ts);
#elif _WIN32
  if (!SleepConditionVariableCS(cond, lock, timeout_ms)) {
    return ETIMEDOUT;
  }
  return 0;
#else
  return 0;
#endif
}

/**
 * Destroys the condition variable specified by cond
 *
 * @param[in] cond The condition variable
 *
 * @return exit status
 */
static inline int cond_handle_destroy(cond_handle_t* const cond) {
#ifdef _POSIX_THREADS
  return pthread_cond_destroy(cond);
#elif _WIN32
  return 0;
#else
  return 0;
#endif
}

#ifdef __cplusplus
}
#endif

#endif  // __UTILS_HANDLES_COND_H__
