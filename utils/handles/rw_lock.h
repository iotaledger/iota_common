/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef __UTILS_HANDLES_RW_LOCK_H__
#define __UTILS_HANDLES_RW_LOCK_H__

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
 * We define a type rw_lock_handle_t mapping to a system available read/write
 * lock primitive and its associated functions, some of them might have no
 * effect if not needed by the underlying API
 */
#ifdef _POSIX_THREADS
typedef pthread_rwlock_t rw_lock_handle_t;
#elif _WIN32
typedef SRWLOCK rw_lock_handle_t;
#else
typedef int rw_lock_handle_t;
#endif

/**
 * Initializes a read/write lock
 *
 * @param[in] lock The lock
 *
 * @return exit status
 */
static inline int rw_lock_handle_init(rw_lock_handle_t* const lock) {
#ifdef _POSIX_THREADS
  return pthread_rwlock_init(lock, NULL);
#elif _WIN32
  InitializeSRWLock(lock);
  return 0;
#else
  return 0;
#endif
}

/**
 * Acquires reading ownership of the given read/write lock
 *
 * @param[in] lock The lock
 *
 * @return exit status
 */
static inline int rw_lock_handle_rdlock(rw_lock_handle_t* const lock) {
#ifdef _POSIX_THREADS
  return pthread_rwlock_rdlock(lock);
#elif _WIN32
  AcquireSRWLockShared(lock);
  return 0;
#else
  return 0;
#endif
}

/**
 * Acquires writing ownership of the given read/write lock
 *
 * @param[in] lock The lock
 *
 * @return exit status
 */
static inline int rw_lock_handle_wrlock(rw_lock_handle_t* const lock) {
#ifdef _POSIX_THREADS
  return pthread_rwlock_wrlock(lock);
#elif _WIN32
  AcquireSRWLockExclusive(lock);
  return 0;
#else
  return 0;
#endif
}

/**
 * Releases ownership of the given read/write lock
 *
 * @param[in] lock The lock
 *
 * @return exit status
 */
static inline int rw_lock_handle_unlock(rw_lock_handle_t* const lock) {
#ifdef _POSIX_THREADS
  return pthread_rwlock_unlock(lock);
#elif _WIN32
  void* state = *(void**)lock;

  if (state == (void*)1) {
    ReleaseSRWLockExclusive(lock);
  } else {
    ReleaseSRWLockShared(lock);
  }
  return 0;
#else
  return 0;
#endif
}

/**
 * Destroys the read/write lock
 *
 * @param[in] lock The lock
 *
 * @return exit status
 */
static inline int rw_lock_handle_destroy(rw_lock_handle_t* const lock) {
#ifdef _POSIX_THREADS
  return pthread_rwlock_destroy(lock);
#elif _WIN32
  return 0;
#else
  return 0;
#endif
}

#ifdef __cplusplus
}
#endif

#endif  // __UTILS_HANDLES_RW_LOCK_H__
