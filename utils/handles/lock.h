/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef __UTILS_HANDLES_LOCK_H__
#define __UTILS_HANDLES_LOCK_H__

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
 * We define a type lock_handle_t mapping to a system available lock primitive
 * and its associated functions, some of them might have no effect if not needed
 * by the underlying API
 */

#ifdef _POSIX_THREADS
typedef pthread_mutex_t lock_handle_t;
#elif _WIN32
typedef CRITICAL_SECTION lock_handle_t;
#else  // disable locker
typedef int lock_handle_t;
#endif

/**
 * Initializes a lock
 *
 * @param[in] lock The lock
 *
 * @return exit status
 */
static inline int lock_handle_init(lock_handle_t* const lock) {
#ifdef _POSIX_THREADS
  return pthread_mutex_init(lock, NULL);
#elif _WIN32
  InitializeCriticalSection(lock);
  return 0;
#else  // disable locker
  return 0;
#endif
}

/**
 * Acquires ownership of the given lock
 *
 * @param[in] lock The lock
 *
 * @return exit status
 */
static inline int lock_handle_lock(lock_handle_t* const lock) {
#ifdef _POSIX_THREADS
  return pthread_mutex_lock(lock);
#elif _WIN32
  EnterCriticalSection(lock);
  return 0;
#else  // disable locker
  return 0;
#endif
}

/**
 * Releases ownership of the given lock
 *
 * @param[in] lock The lock
 *
 * @return exit status
 */
static inline int lock_handle_unlock(lock_handle_t* const lock) {
#ifdef _POSIX_THREADS
  return pthread_mutex_unlock(lock);
#elif _WIN32
  LeaveCriticalSection(lock);
  return 0;
#else  // disable locker
  return 0;
#endif
}

/**
 * Destroys the lock
 *
 * @param[in] lock The lock
 *
 * @return exit status
 */
static inline int lock_handle_destroy(lock_handle_t* const lock) {
#ifdef _POSIX_THREADS
  return pthread_mutex_destroy(lock);
#elif _WIN32
  DeleteCriticalSection(lock);
  return 0;
#else  // disable locker
  return 0;
#endif
}

#ifdef __cplusplus
}
#endif

#endif  // __UTILS_HANDLES_LOCK_H__
