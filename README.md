# AION-ZERO

**Firmware for AION-ZERO**, a DIY handheld game console powered by the Raspberry Pi Pico 2 W and C++.

AION-ZERO is a personal hardware and software project focused on building a compact handheld gaming device from the ground up.

![Menu](/misc/menu.jpeg)

## What hardware is this software for?
The firmware is designed for the following hardware components:

- **Microcontroller:** Raspberry Pi Pico 2 W / Pico 2 WH
- **Display:** Waveshare Pico-LCD-1.44

### Waveshare Pico-LCD-1.44

The Waveshare Pico-LCD-1.44 is a compact LCD module designed for Raspberry Pi Pico-compatible boards.
- **Documentation:** [Pico-LCD-1.44 Wiki](https://www.waveshare.com/wiki/Pico-LCD-1.44)
- **Driver:** [Pico-LCD-1.44 Driver Library](https://github.com/waveshare/Pico_code/tree/main)

The required driver files are included in the [`lib/`](./lib/) directory.
They have been slightly modified to meet the firmware's specific requirements.

## General architecture idea

All low-level hardware interactions are handled using the **Raspberry Pi Pico SDK** and its associated toolchain.
The firmware is built from scratch without relying on prebuilt game engines, with an emphasis on modularity,
maintainability, and future extensibility.
Games are implemented as independent **modules**, each representing a self-contained subsystem designed to be invoked by the main firmware loop at the user's request.
This architecture allows new games to be added without requiring major changes to the core firmware.

## Compilation and usage

Clone the pico-sdk:
```bash
git clone https://github.com/raspberrypi/pico-sdk
```
Then initialize the submodules inside the cloned repository's root directory:
```bash
git submodule update --init --recursive
```
(Optional for devs) To generate compile commands for the project, create a symlink for the generated compile-commands.json in the root of the AION ZERO repository:
```bash
ln -sf build/compile_commands.json compile_commands.json    
```
Compile the project using the Makefile in the root:
```bash
make
```

To see what's getting printed via USB CDC, run:

```bash
screen /dev/ttyACM0 115200
```

## Games

### Ashforged Blade
The software in version 1.0 features a 2D side-scrollable platformer game: Ashforged Blade.
The game is a self-contained *module* (* see General architecture idea *) and is built on a custom DIY engine in pure C++.

![ASH Menu](/misc/ash_menu.jpeg) ![ASH Gameplay](/misc/ash_game.jpeg)

## Notes

This is a hobby project built for fun and an opportunity for me to take my first steps into embedded software development.
If you find this software useful in any way, feel free to improve it, experiment with it, add a game or any other separate module.
Submit a pull request or fork as you wish :)

## License

MIT License

Copyright (c) 2026 Aleksander Garbacz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
