# TEX Shura

![TEX Shura](https://cdn.shopify.com/s/files/1/0052/5814/9978/products/52809163204_68662770a3_k.jpg?v=1681308309)

A compact keyboard with a TrackPoint and three mouse buttons below the spacebar. TEX sells ANSI,
ISO, JIS and hot-swap variants with several split-key options.

* Keyboard Maintainer: [trapexit](https://github.com/trapexit)
* Hardware Supported: TEX Shura PCB (Holtek HT32F52352), TEX BLE5 or BLE4 add-on board
* Hardware Availability: [TEX](https://tex.com.tw/products/shura)

Build after setting up QMK:

    qmk compile -kb tex/shura -km default

Keep `.build/tex_shura_default.bin` **and** `.build/tex_shura_default.elf` from that build.
The TEX bootloader is not supported by `qmk flash`. Use the Linux
[tex-flash instructions](https://github.com/trapexit/tex-flash#flash-over-usb). Before connecting
the keyboard, you can check the files against the official TEX Shura updater:

    tex-flash check --model shura --updater AP_0532_0.18_20230914.exe \
        --bin .build/tex_shura_default.bin --elf .build/tex_shura_default.elf

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

From QMK, enter the TEX bootloader (USB `04D9:1532`) using one of these methods:

* **Bootmagic reset**: Hold down Escape and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
* **From the host**: on builds with a supported raw HID interface, tex-flash can ask QMK to restart into the bootloader.

These shortcuts are not recovery methods for a board that cannot run its application. The stock
updater contains the application, not a complete backup of the bootloader.

## Notes

* Holding the middle mouse button activates layer 1 and turns TrackPoint motion into scrolling; a
  tap without other input sends a middle click. `SHURA_FN1` to `SHURA_FN3` hold layers 1 to 3.
* DIP switches: 1-3 select a profile for `profile_switch_user()`, 4 lets Fn scroll the TrackPoint,
  5 reverses vertical scrolling. DIP 6 (the stock configuration disk) has no function.
* Keyboard keycodes cover Bluetooth hosts and pairing, TrackPoint sensitivity and vertical speed,
  battery sleep time, and typing a battery report.
* Settings are stored in the board's SPI flash, between the stock firmware's profile and disk
  areas, so returning to the stock firmware keeps its data.
* Bluetooth requires an optional module. The build defaults to BLE5; add `SHURA_BLE_MODULE = ble4`
  to a keymap's `rules.mk` for BLE4, or `BLUETOOTH_ENABLE = no` for USB only. USB and BLE4 have
  been exercised on a Shura. BLE5 and battery reporting have not been hardware-tested by the
  maintainer. On BLE4 the Caps Lock LED does not follow the host.

Adapted from [Mauro DiBenedetto's TEX Shinobi port](https://github.com/cyclistmass/tex-qmk/tree/bf4a40841d3b3ecd226fc2e0ebb09cdc67b1c7da/shinobi).
