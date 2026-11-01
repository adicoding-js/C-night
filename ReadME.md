# C-Night

![PCB RENDER](image-1.png)
![Schematic](<Screenshot 2026-10-28 161236.png>)

A handheld tactical HUD gadget built on an ESP32-S3. It combines a live camera feed, a thermal sensor, a laser pointer, and IR night vision into one device with an on-screen overlay.

## What it does

- Live camera feed (OV3660) pushed straight to an ILI9341 screen
- Thermal sensor (MLX90614) reads object temperature, shown as a HUD overlay
- Laser toggle button
- IR LED toggle for night vision
- HUD color cycle button (red / green / white)
- Shutter button (currently just beeps, no photo save yet)

# What does the firmware does:
- The firmware runs on an ESP32-S3 and drives four main systems: a live camera feed from the OV3660 sensor rendered directly to an ILI9341 display, a non-contact thermal readout from the MLX90614 overlaid on screen, a toggleable laser pointer and IR LED array for night vision, and a HUD color cycle for the on-screen crosshair and text. Button inputs handle all four toggles plus a shutter trigger, which currently only sounds a buzzer since photo/video saving isn’t implemented yet.
## Hardware

- ESP32-S3-DevKitC-1 (N8R8 or N16R8, needs PSRAM)
- OV3660 camera module
- MLX90614 thermal sensor
- ILI9341 TFT display
- Laser diode + IR LEDs
- 4x push buttons, buzzer

Custom PCB handles the laser, IR, thermal sensor, buttons, buzzer, and TFT wiring. Camera connects directly to the devkit.

# BOM

| Part | Specs | Source | Price (₹) | Qty | Link |
|---|---|---|---:|---:|---|
| ESP32-S3-DevKitC-1 | N8R8, 8 MB flash + 8 MB PSRAM | Robu | 1,389 | 1 | [Robu](https://robu.in/product/espressif-esp32-s3-devkitc-1-n8r8-development-board) |
| Camera module | OV3660; M5Stack Timer Camera, self-contained ESP32 + PSRAM camera | Robu | 1,779 | 1 | [Robu](https://robu.in/product/m5stack-esp32-psram-timer-camera-ov3660) |
| MLX90614 | GY-906 non-contact IR thermometer, I²C | Robu | 779 | 1 | [Robu](https://robu.in/?p=717378) |
| ILI9341 TFT | 2.8", SPI, 240×320 | Robu | 599–749 | 1 | [Robu](https://robu.in/?p=62026) |
| Laser diode module | 650 nm, 5 mW, 5 V | Robu | 10–32 | 1 | [Robu](https://robu.in/?p=16339) |
| IR emitter LEDs | 5 mm, 940 nm infrared transmitter LED | Amazon India | Under ₹150 per pack | 6 | Search Amazon: “5mm 940nm IR emitter LED pack” |
| AO3400 MOSFET | N-channel, SOT-23, 30 V / 5.8 A | Robu | Low-cost single unit | 1 | [Robu AO3400-HXY](https://robu.in/product/ao3400-hxy-mosfet-30v-5-8a-30m%25cf%258910v5-8a-1-4w-700mv-1-n-channel-sot-23-mosfets-rohs/) |
| S8050 transistor | NPN BJT, TO-92 package, 25 V / 500 mA | Robu | 3.70 | 3 | [Robu S8050 TO-92](https://robu.in/product/s8050range160-300-jcet-25v-625mw-160500ma1v-500ma-npn-to-92-3-bipolar-bjt-rohs/) |
| Buzzer | 5 V active electromagnetic buzzer, PCB mount | Robu | 11 | 1 | [Robu 5 V active buzzer](https://robu.in/product/5v-active-electromagnetic-buzzer-pack-of-5/) |
| Tactile push buttons | 12×12 mm, 4-pin, momentary, through-hole | Robocraze | Check product page | 4 | [Robocraze tactile buttons](https://robocraze.com/products/tactile-12x12x8mm-4-pin-push-button-switch-pack-of-5) |
| Resistors | 1/4 W metal-film assortment, 10 Ω–1 MΩ | Robu | Kit price on page | Misc | [Robu Plusivo resistor kit](https://robu.in/brand/plusivo/) |
| Capacitors | Ceramic + electrolytic component assortment | Robu | Kit price on page | Misc | [Robu component kits](https://robu.in/product-category/electronic-components/component-kits/) |

## Notes for BOM

- Use **IR emitter/transmitter LEDs**, not Robu’s 5 mm 940 nm IR receiver LED.
- The AO3400 is suitable for low-side switching of the IR LED string.
- The S8050 TO-92 version is easier to use on a breadboard than SOT-23.
- The buzzer listing is a pack of five; buy one pack and use one unit.
- The push-button listing is a pack of five; buy one pack and use four units.
- Buy resistors and capacitors as assortments rather than individual values.