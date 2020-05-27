/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef COMMON_LOGGER_HELPER_H_
#define COMMON_LOGGER_HELPER_H_

#include <stdbool.h>
#include <stdint.h>

#include "common/errors.h"

#ifdef USE_EMBEAR_LOGGER
#include "logger.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef USE_EMBEAR_LOGGER
typedef int16_t logger_id_t;
typedef uint16_t logger_level_t;
#define LOGGER_UNKNOWN ((logger_level_t)(0))
#define LOGGER_DEBUG ((logger_level_t)(1 << 0))
#define LOGGER_INFO ((logger_level_t)(1 << 1))
#define LOGGER_NOTICE ((logger_level_t)(1 << 2))
#define LOGGER_WARNING ((logger_level_t)(1 << 3))
#define LOGGER_ERR ((logger_level_t)(1 << 4))
#define LOGGER_CRIT ((logger_level_t)(1 << 5))
#define LOGGER_ALERT ((logger_level_t)(1 << 6))
#define LOGGER_EMERG ((logger_level_t)(1 << 7))
#define LOGGER_ALL ((logger_level_t)((1 << 8) - 1))
#endif

typedef struct logger_t logger_t;

#define log_debug(id, ...) logger_helper_print(id, LOGGER_DEBUG, __VA_ARGS__)
#define log_info(id, ...) logger_helper_print(id, LOGGER_INFO, __VA_ARGS__)
#define log_notice(id, ...) logger_helper_print(id, LOGGER_NOTICE, __VA_ARGS__)
#define log_warning(id, ...) logger_helper_print(id, LOGGER_WARNING, __VA_ARGS__)
#define log_error(id, ...) logger_helper_print(id, LOGGER_ERR, __VA_ARGS__)
#define log_critical(id, ...) logger_helper_print(id, LOGGER_CRIT, __VA_ARGS__)
#define log_alert(id, ...) logger_helper_print(id, LOGGER_ALERT, __VA_ARGS__)
#define log_emergency(id, ...) logger_helper_print(id, LOGGER_EMERG, __VA_ARGS__)

/**
 * @brief Init the logger instance
 *
 * @param level debug level of logger
 * @return retcode_t
 */
retcode_t logger_helper_init(logger_level_t level);

/**
 * @brief Cleanup the logger instance
 *
 * @return retcode_t
 */
retcode_t logger_helper_destroy();

/**
 * @brief Enable
 *
 * @param logger_name logger name
 * @param level debug level
 * @param enable_color true: logger text with color
 * @return logger_id_t
 */
logger_id_t logger_helper_enable(char const* const logger_name, logger_level_t const level, bool const enable_color);

/**
 * @brief Cleanup logger by ID
 *
 * @param logger_id logger ID
 */
void logger_helper_release(logger_id_t const logger_id);

/**
 * @brief print implementation
 *
 * @param logger_id logger ID
 * @param level logger level
 * @param format formater
 * @param ...
 */
void logger_helper_print(logger_id_t const logger_id, logger_level_t const level, char const* const format, ...);

#ifdef __cplusplus
}
#endif

#endif  // COMMON_LOGGER_HELPER_H_
