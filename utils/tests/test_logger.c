/*
 * Copyright (c) 2020 IOTA Stiftung
 * https://github.com/iotaledger/iota_common
 *
 * Refer to the LICENSE file for licensing information
 */

#include <unity/unity.h>

#include "utils/logger_helper.h"

// for displaying current logger only, not a real test case.
void test_logger() {
  logger_helper_init(LOGGER_DEBUG);
  logger_id_t test_logger_id = logger_helper_enable("test_logger", LOGGER_DEBUG, true);
  log_debug(test_logger_id, "[%s:%d] DEBUG.\n", __func__, __LINE__);
  log_warning(test_logger_id, "[%s:%d] WARN.\n", __func__, __LINE__);
  log_error(test_logger_id, "[%s:%d] ERROR.\n", __func__, __LINE__);
  logger_helper_release(test_logger_id);
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_logger);

  return UNITY_END();
}
