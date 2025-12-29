/*
 * Copyright (c) 2025 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico.h"

// Bare-metal stub so __libc_fini_array can resolve _fini without pulling in
// hosted runtime shutdown logic.
void __weak _fini(void) {}
