## ESP32-Repo

Using ESP-IDF Build 11.03.18 (MSYS2)

**Updates: 04.08.2018**

Espressif have added a [new build system `cmake`](https://docs.espressif.com/projects/esp-idf/en/feature-cmake/get-started/) to their compilation


## Steps

- [Getting Started with MSYS2](#getting-started-with-msys2)
    - [Default Configuration](#default-configuration)
- [Getting Started with CMAKE Build System](#getting-started-with-cmake-build-system)
    - [Problems with Setting up `idf.py` with Windows](#problems-with-setting-up-idfpy-with-windows)
        - [My Fix](#my-fix)
- [FreeRTOS Examples](#freertos-examples)
        - [DONE](#done)
        - [TODO](#todo)
- [ESP32 Examples](#esp32-examples)
        - [TODO](#todo)


# Getting Started with MSYS2

## Default Configuration

[Github Link for IDF Repository](https://github.com/espressif/esp-idf)

* [Setting up the toolchain for windows](https://esp-idf.readthedocs.io/en/latest/get-started/windows-setup.html)

* [Setting up the toolchain with Eclipse CDT for windows](https://esp-idf.readthedocs.io/en/v2.0/eclipse-setup-windows.html#eclipse-windows-setup)

# Getting Started with CMAKE Build System

[Installing Toolchain and Getting Started](https://docs.espressif.com/projects/esp-idf/en/feature-cmake/get-started/)

[Integrating with VSCode](https://github.com/Deous/VSC-Guide-for-esp32)

## Problems with Setting up `idf.py` with Windows

If Python3 has precedence over Python2 in Windows

`py -2 idf.py`

`C:\Python27\python.exe idf.py`

both might not work

### My Fix

- Goto `%IDF_PATH%\tools`
- Open idf.py in your text editor
- Change the first line

(Change this)
`#!/usr/bin/env python`

(To this)
`#!/usr/bin/env python2` 

- Go to `C:\Python27`
- Change `python.exe` to `python2.exe`

**Note: This still does not work with Windows Command Prompt**

- Install `Git` for Windows and add it to PATH
- Open `cmd` and type `sh` or `bash`
- run `idf.py` and it should work (SUCCESS)

# FreeRTOS Examples

These examples work with the `ESP32 Devkit V1 board`

Examples taken from the [FreeRTOS Books and Manuals](https://www.freertos.org/Documentation/RTOS_book.html)

### DONE

1. Tasks
2. Queues
3. Software Timers

### TODO

1. Interrupts
1. Resources
1. Event Groups
1. Task Notifications

> Add more later

# ESP32 Examples

These are ESP32 specific examples

### TODO

1. Peripherals
1. BLE
1. Wi-Fi

> Add more later
