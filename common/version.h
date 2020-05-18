/*
 * Copyright (c) 2020 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef __COMMON_VERSION_H__
#define __COMMON_VERSION_H__

#ifdef __cplusplus
extern "C" {
#endif

#define IOTA_COMMON_VERSION_MAJOR 1
#define IOTA_COMMON_VERSION_MINOR 1
#define IOTA_COMMON_VERSION_MICRO 0
#define IOTA_COMMON_VERSION_SPECIAL "beta"

#define VER_STR0(s) #s
#define VER_STR(s) VER_STR0(s)

#define IOTA_COMMON_VERSION          \
  VER_STR(IOTA_COMMON_VERSION_MAJOR) \
  "." VER_STR(IOTA_COMMON_VERSION_MINOR) "." VER_STR(IOTA_COMMON_VERSION_MICRO) "-" IOTA_COMMON_VERSION_SPECIAL

#ifdef __cplusplus
}
#endif

#endif  // __COMMON_VERSION_H__
