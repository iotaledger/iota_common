/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef USE_EMBEAR_LOGGER
#include <stdarg.h>
#endif

#include "utils/handles/lock.h"
#include "utils/logger_helper.h"

static lock_handle_t lock;

retcode_t logger_helper_init(logger_level_t level) {
#ifdef USE_EMBEAR_LOGGER
  if (LOGGER_VERSION != logger_version()) {
    return RC_UTILS_INVALID_LOGGER_VERSION;
  }

  logger_init();
  logger_color_prefix_enable();
  logger_color_message_enable();
  logger_output_register(stdout);
  logger_output_level_set(stdout, level);
#else
  (void)level;
#endif
  lock_handle_init(&lock);
  return RC_OK;
}

retcode_t logger_helper_destroy() {
#ifdef USE_EMBEAR_LOGGER
  logger_output_deregister(stdout);
#endif
  lock_handle_destroy(&lock);
  return RC_OK;
}

logger_id_t logger_helper_enable(char const* const logger_name, logger_level_t const level, bool const enable_color) {
  logger_id_t logger_id = 0;
  lock_handle_lock(&lock);
#ifdef USE_EMBEAR_LOGGER
  logger_id = logger_id_request(logger_name);
  logger_id_enable(logger_id);
  logger_id_level_set(logger_id, level);
  logger_id_prefix_set(logger_id, (LOGGER_PFX_DATE | LOGGER_PFX_NAME | LOGGER_PFX_LEVEL));
  if (enable_color) {
    logger_id_color_console_set(logger_id, LOGGER_FG_GREEN, LOGGER_BG_BLACK,
                                LOGGER_ATTR_BRIGHT | LOGGER_ATTR_UNDERLINE);
  }
#else
  (void)logger_name;
  (void)level;
  (void)enable_color;
#endif
  lock_handle_unlock(&lock);
  return logger_id;
}

void logger_helper_release(logger_id_t const logger_id) {
  lock_handle_lock(&lock);
#ifdef USE_EMBEAR_LOGGER
  logger_id_release(logger_id);
#else
  (void)logger_id;
#endif
  lock_handle_unlock(&lock);
}

void logger_helper_print(logger_id_t const logger_id, logger_level_t const level, char const* const format, ...) {
  va_list argp;

#ifdef USE_EMBEAR_LOGGER
  if (level < logger_output_level_get(stdout)) {
    return;
  }
#else
  (void)logger_id;
  (void)level;
#endif

  va_start(argp, format);
  lock_handle_lock(&lock);
#ifdef USE_EMBEAR_LOGGER
  logger_va(logger_id, level, format, argp);
#else
  vprintf(format, argp);
#endif
  lock_handle_unlock(&lock);
  va_end(argp);
}
