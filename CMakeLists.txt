#[[
Copyright (c) 2019 IOTA Stiftung
https://github.com/iotaledger/iota_common

Refer to the LICENSE file for licensing information
]]

cmake_minimum_required(VERSION 3.5)

cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})

if(${CMAKE_VERSION} VERSION_LESS "3.9.6")
  project(iota_common)
else()
  project(iota_common DESCRIPTION "IOTA Common Library")
endif()

enable_language(C)
enable_testing()

option(TRINARY_TEST "Trinary tests" OFF)
option(ENABLE_ASAN "Enable Address sanitizer" OFF)

#Trit Encoding flags
option(TE_1 "Trit encoding 1 trit per byte" OFF)
option(TE_3 "Trit encoding 3 trits per byte" ON)
option(TE_4 "Trit encoding 4 trits per byte" OFF)

# PCurl configuration flags
option(PCURL_SBOX_UNWIND_2 "Unwind 2 rounds of PCurl sbox" ON)
option(PCURL_SBOX_UNWIND_4 "Unwind 4 rounds of PCurl sbox" OFF)
option(PCURL_SBOX_UNWIND_8 "Unwind 8 rounds of PCurl sbox" OFF)
option(PCURL_STATE_DOUBLE "Use PCurl double state; PCurl short state optimization is enabled by default" OFF)

option(TE_5 "Trit encoding 5 trits per byte" OFF)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include(ExternalProject)

# libs in the sandbox
#link_directories("${PROJECT_BINARY_DIR}/lib")
link_directories("${CMAKE_INSTALL_PREFIX}/lib")

# external libs
include(cmake/embear_logger.cmake)
include(cmake/keccak.cmake)
include(cmake/unity.cmake)
include(cmake/uthash.cmake)

if(ENABLE_ASAN AND TRINARY_TEST)
  include(cmake/asan.cmake)
endif()

set(COMMON_TRINARY_DIR "common/trinary")
set(COMMON_CRYPTO_DIR "common/crypto")
set(COMMON_HELPERS_DIR "common/helpers")
set(COMMON_MODEL_DIR "common/model")
set(COMMON_SRC
  # error code
  "common/errors.c"
  # trynary
  "${COMMON_TRINARY_DIR}/add.c"
  "${COMMON_TRINARY_DIR}/flex_trit.c"
  "${COMMON_TRINARY_DIR}/ptrit.c"
  "${COMMON_TRINARY_DIR}/ptrit_incr.c"
  "${COMMON_TRINARY_DIR}/trit_byte.c"
  "${COMMON_TRINARY_DIR}/trit_long.c"
  "${COMMON_TRINARY_DIR}/trit_tryte.c"
  "${COMMON_TRINARY_DIR}/tryte_ascii.c"
  "${COMMON_TRINARY_DIR}/tryte_long.c"
  "${COMMON_TRINARY_DIR}/tryte.c"
  # curl
  "${COMMON_CRYPTO_DIR}/curl-p/const.c"
  "${COMMON_CRYPTO_DIR}/curl-p/curl_p.c"
  "${COMMON_CRYPTO_DIR}/curl-p/digest.c"
  "${COMMON_CRYPTO_DIR}/curl-p/hashcash.c"
  "${COMMON_CRYPTO_DIR}/curl-p/pearl_diver.c"
  "${COMMON_CRYPTO_DIR}/curl-p/ptrit.c"
  # kerl
  "${COMMON_CRYPTO_DIR}/kerl/bigint.c"
  "${COMMON_CRYPTO_DIR}/kerl/converter.c"
  "${COMMON_CRYPTO_DIR}/kerl/kerl.c"
  "${COMMON_CRYPTO_DIR}/kerl/hash.c"
  # sign
  "${COMMON_CRYPTO_DIR}/iss/v1/iss_curl.c"
  "${COMMON_CRYPTO_DIR}/iss/v1/iss_kerl.c"
  "${COMMON_CRYPTO_DIR}/iss/normalize.c"
  # helpers
  "${COMMON_HELPERS_DIR}/checksum.c"
  "${COMMON_HELPERS_DIR}/digest.c"
  "${COMMON_HELPERS_DIR}/sign.c"
  "${COMMON_HELPERS_DIR}/pow.c"
  # models
  "${COMMON_MODEL_DIR}/bundle.c"
  "${COMMON_MODEL_DIR}/transaction.c"
  "${COMMON_MODEL_DIR}/transfer.c"
)

set(HASH_CONTAINERS_DIR "utils/containers/hash")
# genrate hash containers
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}")
add_custom_command(
  OUTPUT
  "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}/hash27_queue.c"
  "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}/hash81_queue.c"
  "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}/hash243_queue.c"
  "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}/hash6561_queue.c"
  "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}/hash8019_queue.c"
  "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}/hash27_stack.c"
  "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}/hash81_stack.c"
  "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}/hash243_stack.c"
  "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}/hash6561_stack.c"
  "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}/hash8019_stack.c"
  "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}/hash27_queue.h"
  "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}/hash81_queue.h"
  "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}/hash243_queue.h"
  "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}/hash6561_queue.h"
  "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}/hash8019_queue.h"
  "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}/hash27_stack.h"
  "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}/hash81_stack.h"
  "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}/hash243_stack.h"
  "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}/hash6561_stack.h"
  "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}/hash8019_stack.h"
  COMMAND "./cmake/gen_hash_container.sh" ARGS "${PROJECT_BINARY_DIR}/${HASH_CONTAINERS_DIR}"
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

set(UTILS_SRC
  "utils/time.c"
  "utils/logger_helper.c"
  "utils/char_buffer.c"
  "utils/memset_safe.c"
  "utils/system.c"
  "utils/input_validators.c"
  # hash container
  "${HASH_CONTAINERS_DIR}/hash_array.c"
  "${HASH_CONTAINERS_DIR}/hash27_queue.c"
  "${HASH_CONTAINERS_DIR}/hash81_queue.c"
  "${HASH_CONTAINERS_DIR}/hash243_queue.c"
  "${HASH_CONTAINERS_DIR}/hash6561_queue.c"
  "${HASH_CONTAINERS_DIR}/hash8019_queue.c"
  "${HASH_CONTAINERS_DIR}/hash27_stack.c"
  "${HASH_CONTAINERS_DIR}/hash81_stack.c"
  "${HASH_CONTAINERS_DIR}/hash243_stack.c"
  "${HASH_CONTAINERS_DIR}/hash6561_stack.c"
  "${HASH_CONTAINERS_DIR}/hash8019_stack.c"
)

add_library(common
  "${COMMON_SRC}"
  "${UTILS_SRC}"
)

target_include_directories(common PUBLIC 
  "${PROJECT_SOURCE_DIR}"
  "${PROJECT_BINARY_DIR}" # looking for generated sources
  #"${PROJECT_BINARY_DIR}/include"
  "${CMAKE_INSTALL_PREFIX}/include"
  "${CMAKE_INSTALL_PREFIX}/include/keccak"
)

add_dependencies(common
  ext_uthash
  ext_keccak
  ext_embear_logger
)

if(HAS_ASAN_ENABLED)
  target_link_libraries(common PUBLIC asan)
endif()

target_link_libraries(common PUBLIC 
  Threads::Threads
  keccak
  logger)

# install
install(TARGETS common DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
install(DIRECTORY "${PROJECT_SOURCE_DIR}/common/" DESTINATION "${CMAKE_INSTALL_PREFIX}/include/common" FILES_MATCHING PATTERN "*.h")
install(DIRECTORY "${PROJECT_SOURCE_DIR}/utils/" DESTINATION "${CMAKE_INSTALL_PREFIX}/include/utils" FILES_MATCHING PATTERN "*.h")
install(DIRECTORY "${PROJECT_BINARY_DIR}/utils/containers/hash/" DESTINATION "${CMAKE_INSTALL_PREFIX}/include/utils/containers/hash" FILES_MATCHING PATTERN "*.h")

if(${TE_1})
  target_compile_definitions(common PUBLIC "-DFLEX_TRIT_ENCODING_1_TRIT_PER_BYTE")
elseif(${TE_3})
  target_compile_definitions(common PUBLIC "-DFLEX_TRIT_ENCODING_3_TRITS_PER_BYTE")
elseif(${TE_4})
  target_compile_definitions(common PUBLIC "-DFLEX_TRIT_ENCODING_4_TRITS_PER_BYTE")
elseif(${TE_5})
  target_compile_definitions(common PUBLIC "-DFLEX_TRIT_ENCODING_5_TRITS_PER_BYTE")
else()
  #default to TE_3
  target_compile_definitions(common PUBLIC "-DFLEX_TRIT_ENCODING_3_TRITS_PER_BYTE")
endif()


if(${PCURL_SBOX_UNWIND_8})
  target_compile_definitions(common PRIVATE "-DPCURL_SBOX_UNWIND_8")
elseif(${PCURL_SBOX_UNWIND_4})
  target_compile_definitions(common PRIVATE "-DPCURL_SBOX_UNWIND_4")
elseif(${PCURL_SBOX_UNWIND_2})
  target_compile_definitions(common PRIVATE "-DPCURL_SBOX_UNWIND_2")
else()
  # Unwind 2 loops by default
  target_compile_definitions(common PRIVATE "-DPCURL_SBOX_UNWIND_2")
endif()

if(${PCURL_STATE_DOUBLE})
  target_compile_definitions(common PRIVATE "-DPCURL_STATE_DOUBLE")
else()
  target_compile_definitions(common PRIVATE "-DPCURL_STATE_SHORT")
endif()

#if(${RPI_CROSS_COMPILATION})
#  set_property(TARGET common PROPERTY C_STANDARD 99)
#endif()

##=======================TESTING========================

if(${TRINARY_TEST})
  # ==============API test cases================
  function(add_trinary_test test_src test_name)
    add_executable(${test_name} "common/trinary/tests/${test_src}")
    #if(${RPI_CROSS_COMPILATION})
    #  set_property(TARGET ${test_name} PROPERTY C_STANDARD 99)
    #endif()
    target_include_directories(${test_name} PUBLIC ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})
    add_dependencies(${test_name} common)
    if(HAS_ASAN_ENABLED)
      target_link_libraries(${test_name} PRIVATE asan)
    endif()
    target_link_libraries(${test_name} PUBLIC common unity)
    add_test(${test_name} ${test_name})
  endfunction(add_trinary_test)

  add_trinary_test("test_add.c" "test_trinary_add")
  add_trinary_test("test_flex_trit.c" "test_trinary_flex_trit")
  add_trinary_test("test_ptrits.c" "test_trinary_ptrits")
  add_trinary_test("test_trit_byte.c" "test_trinary_trit_byte")
  add_trinary_test("test_trit_long.c" "test_trinary_trit_long")
  add_trinary_test("test_trit_ptrit.c" "test_trinary_trit_ptrit")
  add_trinary_test("test_tryte_ascii.c" "test_trinary_tryte_ascii")
  #add_trinary_test("test_tryte_long.c" "test_trinary_tryte_long")

  function(add_utils_test test_src test_name)
    add_executable(${test_name} "utils/tests/${test_src}")
    target_include_directories(${test_name} PUBLIC ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})
    add_dependencies(${test_name} common)
    target_link_libraries(${test_name} PUBLIC common unity)
    add_test(${test_name} ${test_name})
  endfunction(add_utils_test)

  add_utils_test("test_input_validators.c" "test_input_validators")
endif()

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)
