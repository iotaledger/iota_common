/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef __UTILS_HANDLES_SIGNAL_H__
#define __UTILS_HANDLES_SIGNAL_H__

/**
 * We declare a function signal_handle_register() to handle signals while the
 * program is running
 */

#include <signal.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __APPLE__ || __MACH__
typedef sig_t signal_handle_t;
#else
typedef void (*signal_handle_t)(int);
#endif

static inline signal_handle_t signal_handle_register(int sig, signal_handle_t handler) { return signal(sig, handler); }

#ifdef __cplusplus
}
#endif

#endif  // __UTILS_HANDLES_SIGNAL_H__
