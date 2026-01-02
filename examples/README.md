# Building without USB/stdio using LLVM Embedded Toolchain

For bare-metal targets that don’t need USB stdio, configure with the LLVM Embedded Toolchain sysroot and skip picotool/UF2. Example (building `led_blink` on pico2):
```
rm -rf build
cmake -G Ninja -S examples -B build -DPICO_BOARD=pico2 \
  -DPICO_COMPILER=pico_arm_cortex_m33_clang \
  -DPICO_TOOLCHAIN_PATH=/stuff/tools/llvm/ATfE-21.1.1 \
  -DPICO_COMPILER_SYSROOT=/stuff/tools/llvm/ATfE-21.1.1/lib/clang-runtimes/arm-none-eabi/armv8m.main_hard_fp_exn_rtti_unaligned_size \
  -DPICO_NO_PICOTOOL=1 \
  -DCMAKE_TRY_COMPILE_PLATFORM_VARIABLES="PICO_COMPILER_SYSROOT;PICO_CLANG_RUNTIMES;PICO_CLIB"  \
  -DCMAKE_C_STANDARD_INCLUDE_DIRECTORIES="/stuff/tools/llvm/ATfE-21.1.1/lib/clang-runtimes/arm-none-eabi/include/" \
  -DCMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES="/stuff/tools/llvm/ATfE-21.1.1/lib/clang-runtimes/arm-none-eabi/include/c++/v1/;/stuff/tools/llvm/ATfE-21.1.1/lib/clang-runtimes/arm-none-eabi/include/"

cmake --build build
```

Adjust paths for your toolchain install; some ATfE versions add a `_size` suffix to the runtime directory. Re-enable picotool/USB stdio if needed.
