/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#ifdef _WIN32
#include "utils/windows.h"
#else
#include <sys/time.h>
#if _POSIX_C_SOURCE >= 199309L  // IEEE 1003.1b-1993
#include <time.h>               // for nanosleep
#else
#include <unistd.h>  // for usleep
#endif
#endif

#include "utils/time.h"

uint64_t current_timestamp_ms() {
#ifdef _WIN32
  __int64 wintime;

  GetSystemTimeAsFileTime((FILETIME*)&wintime);
  wintime -= 116444736000000000LL;

  return wintime / 10000LL;
#else
  struct timeval tv = {0, 0};

  gettimeofday(&tv, NULL);
  uint64_t ms = tv.tv_sec * 1000ULL + tv.tv_usec / 1000ULL;
  return ms;
#endif
}

void sleep_ms(uint64_t milliseconds) {
#ifdef _WIN32
  Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
  struct timespec ts;
  ts.tv_sec = milliseconds / 1000;
  ts.tv_nsec = (milliseconds % 1000) * 1000000;
  nanosleep(&ts, NULL);
#else
  usleep(milliseconds * 1000);
#endif
}
