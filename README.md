## ESP32-Repo

**Updated: 15.10.2018**

Espressif have added a [new build system `cmake`](https://docs.espressif.com/projects/esp-idf/en/latest/get-started-cmake/index.html) to their compilation

## Steps

- [Getting Started with MSYS2](#getting-started-with-msys2)
    - [Default Configuration](#default-configuration)
- [Getting Started with CMAKE Build System](#getting-started-with-cmake-build-system)
- [Folder Structure](#folder-structure)

# Getting Started with MSYS2

## Default Configuration

[Github Link for IDF Repository](https://github.com/espressif/esp-idf)

* [Setting up the toolchain for windows](https://esp-idf.readthedocs.io/en/latest/get-started/windows-setup.html)

* [Setting up the toolchain with Eclipse CDT for windows](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/eclipse-setup.html)

# Getting Started with CMAKE Build System

[Installing Toolchain and Getting Started](https://docs.espressif.com/projects/esp-idf/en/latest/get-started-cmake/index.html)

[Integrating with VSCode](https://github.com/Deous/VSC-Guide-for-esp32)

**NOTE**

`idf.py` has been updated. The previous issue of python3 preceding over python2 no longer affects idf.py functionality

# Folder Structure

- Arduino
    - ESP32 Arduino Core
- Esp32
    - ESP32 IDF Core
- FreeRTOS
    - ESP32 FreeRTOS Examples
- Configuration README
    - Configuring your ESP32 environment
- Project Configs
    - `CMake` and `MSYS2` configured projects
