#[[
Copyright (c) 2019 IOTA Stiftung
https://github.com/iotaledger/iota_common

Refer to the LICENSE file for licensing information
]]

if (NOT __KECCAK_INCLUDED)
  set(__KECCAK_INCLUDED TRUE)

  ExternalProject_Add(
    keccak_download
    PREFIX ${PROJECT_BINARY_DIR}/keccak
    DOWNLOAD_DIR ${PROJECT_BINARY_DIR}/download
    DOWNLOAD_NAME keccak_87944d97ee18978a.tar.gz
    URL https://github.com/XKCP/XKCP/archive/a7a105cefc172178c3c9bb7e5f0768e0b226016b.tar.gz
    URL_HASH SHA256=245418d6dd84c7eabfa77c93c5b0eff32c405e691048589bb8d6a253d139bfa3
    CONFIGURE_COMMAND ""
    INSTALL_COMMAND ""
    BUILD_COMMAND ""
    # for debug
    # LOG_DOWNLOAD 1
  )

  set(keccak_cmake_dir ${PROJECT_BINARY_DIR}/keccak/src/ext_keccak)
  set(keccak_src_dir ../keccak_download)
  set(keccak_install_include ${CMAKE_INSTALL_PREFIX}/include/keccak)
  set(keccak_install_lib ${CMAKE_INSTALL_PREFIX}/lib)

  file(WRITE ${keccak_cmake_dir}/CMakeLists.txt
    "cmake_minimum_required(VERSION 3.5)\n"
    "project(keccak C)\n"
    "set(my_src ${keccak_src_dir}/lib/low/KeccakP-1600/Reference/KeccakP-1600-reference.c\n"
    "${keccak_src_dir}/lib/high/Keccak/KeccakSpongeWidth1600.c\n"
    "${keccak_src_dir}/lib/high/Keccak/FIPS202/KeccakHash.c)\n"
    "add_library(keccak STATIC \${my_src})\n"
    "target_include_directories(keccak\n"
    "PUBLIC ${keccak_src_dir}/lib/common\n"
    "PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Reference \n"
    "PUBLIC ${keccak_src_dir}/lib/high/Keccak)\n"
    "install(TARGETS keccak DESTINATION ${CMAKE_INSTALL_PREFIX}/lib )\n"
    "install(DIRECTORY ${keccak_src_dir}/lib/high/Keccak/FIPS202/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    "install(DIRECTORY ${keccak_src_dir}/lib/high/Keccak/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    "install(DIRECTORY ${keccak_src_dir}/lib/common/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    "install(DIRECTORY ${keccak_src_dir}/lib/low/KeccakP-1600/Reference/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    )

  ExternalProject_Add(
    ext_keccak
    PREFIX ${PROJECT_BINARY_DIR}/keccak
    DOWNLOAD_COMMAND ""
    BUILD_IN_SOURCE TRUE
    CMAKE_ARGS
      -DCMAKE_INSTALL_PREFIX:STRING=${CMAKE_INSTALL_PREFIX}
    #  -DCMAKE_TOOLCHAIN_FILE:STRING=${CMAKE_TOOLCHAIN_FILE}
    # for debug
    # LOG_CONFIGURE 1
    # LOG_INSTALL 1
  )
  add_dependencies(ext_keccak keccak_download)

endif()