// Copyright 2026 Mauro DiBenedetto
// Copyright 2026 Antonio SJ Musumeci (@trapexit)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "tex_hw.h"

#define BOARD_NAME "TEX Shura"
#define HT32F52352
// Application region above the TEX bootloader: 0x3200 to 0x1FC00.
#define FLASH_SIZE (0x1FC00 - 0x3200)

#if !defined(_FROM_ASM_)
#    ifdef __cplusplus
extern "C" {
#    endif
void boardInit(void);
#    ifdef __cplusplus
}
#    endif
#endif
