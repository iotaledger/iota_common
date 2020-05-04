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
    "project(keccak C ASM)\n"
    "if(POLICY CMP0076)\n"
    "  cmake_policy(SET CMP0076 NEW)\n"
    "endif()\n"
    "\n"
    "# Kerl Optimization\n"
    "option(KERL_REF_32 \"Kerl reference 32bit\" OFF)\n"
    "option(KERL_AsmX86_64 \"Kerl optimized AsmX86-64\" OFF)\n"
    "option(KERL_COMPACT \"Kerl minimizing code and memory sizes for 64bit\" OFF)\n"
    "option(KERL_AVX2 \"Kerl with AVX2 instruction set optimization\" OFF)\n"
    "option(KERL_INPLACE_32 \"Kerl minimizing memory sizes for 32bit\" OFF)\n"
    "option(KERL_64u6 \"Kerl for 64-bit platforms with 6 rounds unrolled\" OFF)\n"
    "option(KERL_64uf \"Kerl for 64-bit platforms with full rounds unrolled\" OFF)\n"
    "option(KERL_T2o1 \"Kerl calls Keccak-p[1600] twice\" OFF)\n"
    "option(KERL_T4o1 \"Kerl calls Keccak-p[1600] four times\" OFF)\n"
    "option(KERL_T4o2 \"Kerl calls Keccak-p[1600]x2 twice\" OFF)\n"
    "option(KERL_T8o1 \"Kerl calls Keccak-p[1600] eight times\" OFF)\n"
    "option(KERL_T8o2 \"Kerl calls Keccak-p[1600]x2 four times\" OFF)\n"
    "option(KERL_T8o4 \"Kerl calls Keccak-p[1600]x4 twice\" OFF)\n"
    "# Kerl times 2 SIMD\n"
    "option(KERL_SIMD128_SSE2u2 \"Kerl SSE2 instruction set, with two rounds unrolled\" OFF)\n"
    "option(KERL_SIMD128_SSE2uf \"Kerl SSE2 instruction set, with full rounds unrolled\" OFF)\n"
    "# Kerl times 4 SIMD\n"
    "option(KERL_SIMD256_AVX2u6 \"Kerl AVX2 instruction set, with 6 rounds unrolled\" OFF)\n"
    "option(KERL_SIMD256_AVX2u12 \"Kerl AVX2 instruction set, with 12 rounds unrolled\" OFF)\n"
    "option(KERL_SIMD256_AVX2uf \"Kerl AVX2 instruction set, with full rounds unrolled\" OFF)\n"
    "# Kerl ARM Optimization\n"
    "option(KERL_INPLACE_ARMv6M \"Kerl minimizing memory sizes for ARMv6M\" OFF)\n"
    "option(KERL_INPLACE_ARMv7M \"Kerl minimizing memory sizes for ARMv7M\" OFF)\n"
    "option(KERL_INPLACE_ARMv7A \"Kerl minimizing memory sizes for ARMv7A\" OFF)\n"
    "option(KERL_ARMv7A_ASM \"Kerl neon optimiaztion for ARMv7A\" OFF)\n"
    "option(KERL_ARMv8A_ASM \"Kerl neon optimiaztion for ARMv8A\" OFF)\n"
    "\n"
    "if(KERL_T8o4)\n"
    "  if((NOT KERL_T4o2) AND (NOT KERL_T4o1))\n"
    "    message(FATAL_ERROR \"KERL_T8o4 needs KERL_T4o2 or KERL_T4o1\")\n"
    "  endif()\n"
    "endif()\n"
    "\n"
    "if(KERL_T8o2)\n"
    "  SET(KERL_T2o1 ON CACHE BOOL FORCE \"Kerl calls Keccak-p[1600] twice\")\n"
    "endif()\n"
    "\n"
    "if(KERL_T4o2)\n"
    "  SET(KERL_T2o1 ON CACHE BOOL FORCE \"Kerl calls Keccak-p[1600] twice\")\n"
    "endif()\n"
    "\n"
    "set(my_src ${keccak_src_dir}/lib/high/Keccak/KeccakSpongeWidth1600.c\n"
    "${keccak_src_dir}/lib/high/Keccak/FIPS202/KeccakHash.c)\n"
    "add_library(keccak STATIC \${my_src})\n"
    "\n"
    "if(KERL_AsmX86_64)\n"
    "  target_compile_options(keccak PUBLIC -fomit-frame-pointer -O2 -g0 -march=native -mtune=native)\n"
    "  target_sources(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/OptimizedAsmX86-64/KeccakP-1600-x86-64-gas.s)\n"
    "elseif(KERL_AVX2)\n"
    "  target_compile_options(keccak PUBLIC -fomit-frame-pointer -O2 -g0 -march=native -mtune=native)\n"
    "  target_sources(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/OptimizedAVX2/KeccakP-1600-AVX2.s)\n"
    "elseif(KERL_COMPACT)\n"
    "  target_compile_options(keccak PUBLIC -fomit-frame-pointer -O2 -g0 -march=native -mtune=native)\n"
    "  target_sources(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Compact64/KeccakP-1600-compact64.c)\n"
    "elseif(KERL_INPLACE_32)\n"
    "  target_compile_options(keccak PUBLIC -fomit-frame-pointer -O2 -g0 -march=native -mtune=native)\n"
    "  target_sources(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Inplace32BI/KeccakP-1600-inplace32BI.c)\n"
    "elseif(KERL_REF_32)\n"
    "  target_sources(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Reference32BI/KeccakP-1600-reference32BI.c)\n"
    "elseif(KERL_64u6 OR KERL_64uf)\n"
    "  target_compile_options(keccak PUBLIC -fomit-frame-pointer -O2 -g0 -march=native -mtune=native)\n"
    "  target_sources(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized64/KeccakP-1600-opt64.c)\n"
    "elseif(KERL_INPLACE_ARMv6M)\n"
    "  target_compile_options(keccak PUBLIC -fomit-frame-pointer -O2 -g0 -march=native -mtune=native)\n"
    "  target_sources(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized32biAsmARM/KeccakP-1600-inplace-32bi-armv6m-le-gcc.s)\n"
    "elseif(KERL_INPLACE_ARMv7M)\n"
    "  target_compile_options(keccak PUBLIC -fomit-frame-pointer -O2 -g0 -march=native -mtune=native)\n"
    "  target_sources(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized32biAsmARM/KeccakP-1600-inplace-32bi-armv7m-le-gcc.s)\n"
    "elseif(KERL_INPLACE_ARMv7A)\n"
    "  target_compile_options(keccak PUBLIC -fomit-frame-pointer -O2 -g0 -march=native -mtune=native)\n"
    "  target_sources(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized32biAsmARM/KeccakP-1600-inplace-32bi-armv7a-le-gcc.s)\n"
    "elseif(KERL_ARMv7A_ASM)\n"
    "  target_compile_options(keccak PUBLIC -mfpu=neon -fomit-frame-pointer -O2 -g0 -march=native -mtune=native)\n"
    "  target_sources(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/OptimizedAsmARM/KeccakP-1600-armv7a-le-neon-gcc.s)\n"
    "elseif(KERL_ARMv8A_ASM)\n"
    "  target_compile_options(keccak PUBLIC -mfpu=neon -fomit-frame-pointer -O2 -g0 -march=native -mtune=native)\n"
    "  target_sources(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized64AsmARM/KeccakP-1600-armv8a-neon.s)\n"
    "else()\n"
    "  target_sources(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Reference/KeccakP-1600-reference.c)\n"
    "endif()\n"
    "\n"
    "if(KERL_T2o1)\n"
    "  target_sources(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times2/FallbackOn1/KeccakP-1600-times2-on1.c)\n"
    "elseif(KERL_T4o1)\n"
    "  target_sources(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times4/FallbackOn1/KeccakP-1600-times4-on1.c)\n"
    "elseif(KERL_T8o1)\n"
    "  target_sources(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times8/FallbackOn1/KeccakP-1600-times8-on1.c)\n"
    "endif()\n"
    "\n"
    "if(KERL_T4o2)\n"
    "  target_sources(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times4/FallbackOn2/KeccakP-1600-times4-on2.c)\n"
    "endif()\n"
    "\n"
    "if(KERL_T8o2)\n"
    "  target_sources(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times8/FallbackOn2/KeccakP-1600-times8-on2.c)\n"
    "elseif(KERL_T8o4)\n"
    "  target_sources(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times8/FallbackOn4/KeccakP-1600-times8-on4.c)\n"
    "endif()\n"
    "\n"
    "if(KERL_SIMD128_SSE2u2 OR KERL_SIMD128_SSE2uf)\n"
    "  target_sources(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times2/SIMD128/KeccakP-1600-times2-SIMD128.c)\n"
    "elseif(KERL_SIMD256_AVX2u6 OR KERL_SIMD256_AVX2u12 OR KERL_SIMD256_AVX2uf)\n"
    "  target_sources(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times4/SIMD256/KeccakP-1600-times4-SIMD256.c)\n"
    "endif()\n"
    "\n"
    "target_include_directories(keccak\n"
    "PUBLIC ${keccak_src_dir}/lib/common\n"
    "PUBLIC ${keccak_src_dir}/lib/high/Keccak)\n"
    "\n"
    "if(KERL_AsmX86_64)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/OptimizedAsmX86-64)\n"
    "elseif(KERL_AVX2)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/OptimizedAVX2)\n"
    "elseif(KERL_COMPACT)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Compact64)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/common)\n"
    "elseif(KERL_INPLACE_32)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Inplace32BI)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/common)\n"
    "elseif(KERL_REF_32)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Reference32BI)\n"
    "elseif(KERL_64u6 OR KERL_64uf)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized64)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/common)\n"
    "elseif(KERL_INPLACE_ARMv6M OR KERL_INPLACE_ARMv7M OR KERL_INPLACE_ARMv7A)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized32biAsmARM)\n"
    "elseif(KERL_ARMv7A_ASM)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/OptimizedAsmARM)\n"
    "elseif(KERL_ARMv8A_ASM)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized64AsmARM)\n"
    "else()\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Reference)\n"
    "endif()\n"
    "\n"
    "if(KERL_T2o1)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times2/FallbackOn1)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/common)\n"
    "elseif(KERL_T4o1)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times4/FallbackOn1)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/common)\n"
    "elseif(KERL_T8o1)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times8/FallbackOn1)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/common)\n"
    "endif()\n"
    "\n"
    "if(KERL_T4o2)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times4/FallbackOn2)\n"
    "endif()\n"
    "\n"
    "if(KERL_T8o2)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times8/FallbackOn2)\n"
    "elseif(KERL_T8o4)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times8/FallbackOn4)\n"
    "endif()\n"
    "\n"
    "if(KERL_64u6)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized64/u6)\n"
    "elseif(KERL_64uf)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized64/ufull)\n"
    "endif()\n"
    "\n"
    "if(KERL_SIMD128_SSE2u2 OR KERL_SIMD128_SSE2uf)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times2/SIMD128)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized)\n"
    "elseif(KERL_SIMD256_AVX2u6 OR KERL_SIMD256_AVX2u12 OR KERL_SIMD256_AVX2uf)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times4/SIMD256)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized)\n"
    "endif()\n"
    "\n"
    "if(KERL_SIMD128_SSE2u2)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times2/SIMD128/SSE2u2)\n"
    "elseif(KERL_SIMD128_SSE2uf)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times2/SIMD128/SSE2ufull)\n"
    "elseif(KERL_SIMD256_AVX2u6)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times4/SIMD256/AVX2u6)\n"
    "elseif(KERL_SIMD256_AVX2u12)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times4/SIMD256/AVX2u12)\n"
    "elseif(KERL_SIMD256_AVX2uf)\n"
    "  target_include_directories(keccak PUBLIC ${keccak_src_dir}/lib/low/KeccakP-1600-times4/SIMD256/AVX2ufull)\n"
    "endif()\n"
    "\n"
    "install(TARGETS keccak DESTINATION ${CMAKE_INSTALL_PREFIX}/lib )\n"
    "install(DIRECTORY ${keccak_src_dir}/lib/high/Keccak/FIPS202/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    "install(DIRECTORY ${keccak_src_dir}/lib/high/Keccak/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    "install(DIRECTORY ${keccak_src_dir}/lib/common/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    "if(KERL_AsmX86_64)\n"
    "  install(DIRECTORY ${keccak_src_dir}/lib/low/KeccakP-1600/OptimizedAsmX86-64/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    "elseif(KERL_AVX2)\n"
    "  install(DIRECTORY ${keccak_src_dir}/lib/low/KeccakP-1600/OptimizedAVX2/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    "elseif(KERL_COMPACT)\n"
    "  install(DIRECTORY ${keccak_src_dir}/lib/low/KeccakP-1600/Compact64/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    "  install(FILES ${keccak_src_dir}/lib/low/common/SnP-Relaned.h DESTINATION ${keccak_install_include})\n"
    "elseif(KERL_INPLACE_32)\n"
    "  install(DIRECTORY ${keccak_src_dir}/lib/low/KeccakP-1600/Inplace32BI/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    "  install(FILES ${keccak_src_dir}/lib/low/common/SnP-Relaned.h DESTINATION ${keccak_install_include})\n"
    "elseif(KERL_REF_32)\n"
    "  install(DIRECTORY ${keccak_src_dir}/lib/low/KeccakP-1600/Reference32BI/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    "elseif(KERL_64u6)\n"
    "  install(FILES ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized64/KeccakP-1600-SnP.h DESTINATION ${keccak_install_include})\n"
    "  install(FILES ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized/KeccakP-1600-unrolling.macros DESTINATION ${keccak_install_include})\n"
    "  install(FILES ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized/KeccakP-1600-64.macros DESTINATION ${keccak_install_include})\n"
    "  install(FILES ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized64/u6/KeccakP-1600-opt64-config.h DESTINATION ${keccak_install_include})\n"
    "elseif(KERL_64uf)\n"
    "  install(FILES ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized64/KeccakP-1600-SnP.h DESTINATION ${keccak_install_include})\n"
    "  install(FILES ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized/KeccakP-1600-unrolling.macros DESTINATION ${keccak_install_include})\n"
    "  install(FILES ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized/KeccakP-1600-64.macros DESTINATION ${keccak_install_include})\n"
    "  install(FILES ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized64/ufull/KeccakP-1600-opt64-config.h DESTINATION ${keccak_install_include})\n"
    "elseif(KERL_INPLACE_ARMv6M OR KERL_INPLACE_ARMv7M OR KERL_INPLACE_ARMv7A)\n"
    "  install(DIRECTORY ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized32biAsmARM/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    "elseif(KERL_ARMv7A_ASM)\n"
    "  install(DIRECTORY ${keccak_src_dir}/lib/low/KeccakP-1600/OptimizedAsmARM/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    "elseif(KERL_ARMv8A_ASM)\n"
    "  install(DIRECTORY ${keccak_src_dir}/lib/low/KeccakP-1600/Optimized64AsmARM/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    "else()\n"
    "  install(DIRECTORY ${keccak_src_dir}/lib/low/KeccakP-1600/Reference/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    "endif()\n"
    "\n"
    "if(KERL_SIMD128_SSE2u2)\n"
    "  install(DIRECTORY ${keccak_src_dir}/lib/low/KeccakP-1600-times2/SIMD128/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    "  install(FILES ${keccak_src_dir}/lib/low/KeccakP-1600-times2/SIMD128/SSE2u2/SIMD128-config.h DESTINATION ${keccak_install_include})\n"
    "elseif(KERL_SIMD128_SSE2uf)\n"
    "  install(DIRECTORY ${keccak_src_dir}/lib/low/KeccakP-1600-times2/SIMD128/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    "  install(FILES ${keccak_src_dir}/lib/low/KeccakP-1600-times2/SIMD128/SSE2ufull/SIMD128-config.h DESTINATION ${keccak_install_include})\n"
    "elseif(KERL_SIMD256_AVX2u6)\n"
    "  install(DIRECTORY ${keccak_src_dir}/lib/low/KeccakP-1600-times4/SIMD256/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    "  install(FILES ${keccak_src_dir}/lib/low/KeccakP-1600-times4/SIMD256/AVX2u6/SIMD256-config.h DESTINATION ${keccak_install_include})\n"
    "elseif(KERL_SIMD256_AVX2u12)\n"
    "  install(DIRECTORY ${keccak_src_dir}/lib/low/KeccakP-1600-times4/SIMD256/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    "  install(FILES ${keccak_src_dir}/lib/low/KeccakP-1600-times4/SIMD256/AVX2u12/SIMD256-config.h DESTINATION ${keccak_install_include})\n"
    "elseif(KERL_SIMD256_AVX2uf)\n"
    "  install(DIRECTORY ${keccak_src_dir}/lib/low/KeccakP-1600-times4/SIMD256/ DESTINATION ${keccak_install_include} FILES_MATCHING PATTERN \"*.h\")\n"
    "  install(FILES ${keccak_src_dir}/lib/low/KeccakP-1600-times4/SIMD256/AVX2ufull/SIMD256-config.h DESTINATION ${keccak_install_include})\n"
    "endif()\n"
    "\n"
    "if(KERL_T2o1)\n"
    "  install(FILES ${keccak_src_dir}/lib/low/KeccakP-1600-times2/FallbackOn1/KeccakP-1600-times2-SnP.h DESTINATION ${keccak_install_include})\n"
    "  install(FILES ${keccak_src_dir}/lib/low/common/PlSnP-Fallback.inc DESTINATION ${keccak_install_include})\n"
    "elseif(KERL_T4o1)\n"
    "  install(FILES ${keccak_src_dir}/lib/low/KeccakP-1600-times4/FallbackOn1/KeccakP-1600-times4-SnP.h DESTINATION ${keccak_install_include})\n"
    "  install(FILES ${keccak_src_dir}/lib/low/common/PlSnP-Fallback.inc DESTINATION ${keccak_install_include})\n"
    "elseif(KERL_T8o1)\n"
    "  install(FILES ${keccak_src_dir}/lib/low/KeccakP-1600-times8/FallbackOn1/KeccakP-1600-times8-SnP.h DESTINATION ${keccak_install_include})\n"
    "  install(FILES ${keccak_src_dir}/lib/low/common/PlSnP-Fallback.inc DESTINATION ${keccak_install_include})\n"
    "endif()\n"
    "\n"
    "if(KERL_T4o2)\n"
    "  install(FILES ${keccak_src_dir}/lib/low/KeccakP-1600-times4/FallbackOn2/KeccakP-1600-times4-SnP.h DESTINATION ${keccak_install_include})\n"
    "endif()\n"
    "\n"
    "if(KERL_T8o2)\n"
    "  install(FILES ${keccak_src_dir}/lib/low/KeccakP-1600-times8/FallbackOn2/KeccakP-1600-times8-SnP.h DESTINATION ${keccak_install_include})\n"
    "elseif(KERL_T8o4)\n"
    "  install(FILES ${keccak_src_dir}/lib/low/KeccakP-1600-times8/FallbackOn4/KeccakP-1600-times8-SnP.h DESTINATION ${keccak_install_include})\n"
    "endif()\n"
    "\n"
    )

  ExternalProject_Add(
    ext_keccak
    PREFIX ${PROJECT_BINARY_DIR}/keccak
    DOWNLOAD_COMMAND ""
    BUILD_IN_SOURCE TRUE
    CMAKE_ARGS
      -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
      -DCMAKE_INSTALL_PREFIX:STRING=${CMAKE_INSTALL_PREFIX}
      -DKERL_AsmX86_64:BOOL=${KERL_AsmX86_64}
      -DKERL_REF_32:BOOL=${KERL_REF_32}
      -DKERL_COMPACT:BOOL=${KERL_COMPACT}
      -DKERL_AVX2:BOOL=${KERL_AVX2}
      -DKERL_INPLACE_32:BOOL=${KERL_INPLACE_32}
      -DKERL_INPLACE_ARMv6M:BOOL=${KERL_INPLACE_ARMv6M}
      -DKERL_INPLACE_ARMv7M:BOOL=${KERL_INPLACE_ARMv7M}
      -DKERL_INPLACE_ARMv7A:BOOL=${KERL_INPLACE_ARMv7A}
      -DKERL_ARMv7A_ASM:BOOL=${KERL_ARMv7A_ASM}
      -DKERL_ARMv8A_ASM:BOOL=${KERL_ARMv8A_ASM}
      -DKERL_SIMD128_SSE2u2:BOOL=${KERL_SIMD128_SSE2u2}
      -DKERL_SIMD128_SSE2uf:BOOL=${KERL_SIMD128_SSE2uf}
      -DKERL_SIMD256_AVX2u6:BOOL=${KERL_SIMD256_AVX2u6}
      -DKERL_SIMD256_AVX2u12:BOOL=${KERL_SIMD256_AVX2u12}
      -DKERL_SIMD256_AVX2uf:BOOL=${KERL_SIMD256_AVX2uf}
      -DKERL_64u6:BOOL=${KERL_64u6}
      -DKERL_64uf:BOOL=${KERL_64uf}
      -DKERL_T2o1:BOOL=${KERL_T2o1}
      -DKERL_T4o1:BOOL=${KERL_T4o1}
      -DKERL_T4o2:BOOL=${KERL_T4o2}
      -DKERL_T8o1:BOOL=${KERL_T8o1}
      -DKERL_T8o2:BOOL=${KERL_T8o2}
      -DKERL_T8o4:BOOL=${KERL_T8o4}
    #  -DCMAKE_TOOLCHAIN_FILE:STRING=${CMAKE_TOOLCHAIN_FILE}
    # for debug
    # LOG_CONFIGURE 1
    # LOG_INSTALL 1
  )
  add_dependencies(ext_keccak keccak_download)

endif()