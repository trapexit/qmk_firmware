# Bluetooth and battery support need a TEX Bluetooth add-on board. SHURA_BLE_MODULE selects its
# driver: ble5 (BLE5 kit, sold for the Shura) or ble4 (the older Shinobi BLE4 kit).
# Keymaps can set BLUETOOTH_ENABLE = no for USB only.
SHURA_BLE_MODULE ?= ble5
ifeq ($(strip $(BLUETOOTH_ENABLE)), yes)
    SRC += $(SHURA_BLE_MODULE).c power.c
    ifeq ($(strip $(SHURA_BLE_MODULE)), ble4)
        OPT_DEFS += -DSHURA_BLE4
    endif
endif
