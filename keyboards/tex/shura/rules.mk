# MCU: Holtek HT32F52352, booted by the TEX bootloader at 0x0000
MCU = cortex-m0plus
ARMV = 6
USE_FPU = no
MCU_FAMILY = HT32
MCU_SERIES = HT32F523xx
MCU_LDSCRIPT = HT32F52352_TEX_SHURA
MCU_STARTUP = ht32f523xx
BOARD = TEX_SHURA
BOOTLOADER = custom

SRC += shura_fn.c shura_trackpoint.c shura_vendor.c wear_leveling_shura.c
# PS/2 host: QMK's GPIO primitives (ps2_io.c) under ps2_vendor.c
SRC += ps2_io.c ps2_vendor.c
BLUETOOTH_DRIVER = custom
FLASH_DRIVER = spi

# The application starts at 0x3200, above the TEX bootloader; point VTOR there.
ADEFS += -DCRT0_VTOR_INIT=1
OPT_DEFS += -DCRT0_AREAS_NUMBER=1
# Keep the ELF program headers out of the region below the application.
LDFLAGS += -Wl,--nmagic
