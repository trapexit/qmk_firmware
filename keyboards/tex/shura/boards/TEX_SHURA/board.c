// Copyright 2026 Mauro DiBenedetto
// Copyright 2026 Antonio SJ Musumeci (@trapexit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "hal.h"

#define SHURA_GPIO_MODE PAL_MODE_HT32_AF(AFIO_GPIO)
#define SHURA_TP_CLOCK PAL_LINE(GPIOB, 3)
#define SHURA_TP_DATA_IN PAL_LINE(GPIOB, 4)
#define SHURA_TP_DATA_OUT PAL_LINE(GPIOB, 5)
#define SHURA_TP_POWER PAL_LINE(GPIOC, 8)
#define SHURA_CAPS_LED PAL_LINE(GPIOC, 10)
#define SHURA_USB_DETECT PAL_LINE(GPIOB, 12)

// Every pin starts in its reset alternate function (AF0, so PA12/PA13 stay SWD), with
// the stock firmware's pull-ups on PA9 (BOOT) and PA12/PA13 (SWD). Owned pins are set
// up by boardInit() and the matrix, Bluetooth and TrackPoint code.
const PALConfig pal_default_config = {
    .setup[0] = {.INE = 1U << 9, .PU = (1U << 9) | (1U << 12) | (1U << 13)},
};

void HardFault_Handler(void);

// A crash restarts into the TEX bootloader, so the keyboard stays flashable.
void HardFault_Handler(void) {
    TEX_ENTER_IAP();
}

void __early_init(void) {
    TEX_WDT_RELOAD();
    ht32_clock_init();
}

void boardInit(void) {
    palSetLineMode(SHURA_TP_CLOCK, SHURA_GPIO_MODE | PAL_MODE_INPUT);
    palSetLineMode(SHURA_TP_DATA_IN, SHURA_GPIO_MODE | PAL_MODE_INPUT);
    palSetLine(SHURA_TP_DATA_OUT);
    palSetLineMode(SHURA_TP_DATA_OUT, SHURA_GPIO_MODE | PAL_MODE_OUTPUT_OPENDRAIN);
    palClearLine(SHURA_TP_POWER);
    palSetLineMode(SHURA_TP_POWER, SHURA_GPIO_MODE | PAL_MODE_OUTPUT_PUSHPULL);
    palSetLine(SHURA_CAPS_LED);
    palSetLineMode(SHURA_CAPS_LED, SHURA_GPIO_MODE | PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(SHURA_USB_DETECT, SHURA_GPIO_MODE | PAL_MODE_INPUT);
    // Enable the HSI's USB-SOF auto-trim, as the stock firmware does; there is no crystal.
    CKCU->HSICR = (CKCU->HSICR & ~0x30U) | 0x23U;
}
