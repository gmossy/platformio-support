by Glenn Mossy


# Arduino Uno-Tests / Microcontroller Sketch Template

This repository is a **template project** for developing and uploading sketches to
Arduino, ESP32, and RP2040-based boards using:

- **PlatformIO** (VS Code / CLI)
- **arduino-cli** (pure CLI, scriptable)

It is intended to be cloned or copied and then customized per board or per
project, while keeping a consistent toolchain and project structure.

---

## Quick Start (What Most People Want)

This section is for anyone who just wants to **plug in a board and upload a
sketch** using **VS Code + PlatformIO**.

1. Install **VS Code**.
2. Install the **PlatformIO IDE** extension from the VS Code marketplace.
3. Clone or download this repository:

   ```bash
   git clone https://github.com/gmossy/platformio-support.git
   cd Uno-Tests
   ```

4. Open the folder in VS Code (`File → Open Folder…`).
5. Let PlatformIO initialize the project (it may download toolchains the first
   time).
6. **Connect your board via USB.**
7. In the PlatformIO status bar, choose the environment that matches your
   board, for example:
   - `env:uno` for an Arduino Uno or compatible AVR board
   - `env:esp32dev` for a typical ESP32 dev board
   - `env:pico` for Raspberry Pi Pico / RP2040 (example)
8. Click **Upload** (arrow icon) or run from the command palette:

   ```bash
   pio run -t upload -e uno       # or esp32dev / pico
   ```

Your board should reset, and the example sketch (multi-LED blink on the Uno
template) will start running.

If the upload fails because of the serial port, run `pio device list` to see
which `/dev/tty.*` or `/dev/cu.*` port your board is on and update
`upload_port` in `platformio.ini` for that environment.

---

## What This Repo Is

This is **Glenn Mossy’s personal template** for building microcontroller
projects across:

- Arduino / AVR boards (Uno, Nano, Mega, etc.)
- ESP32 boards
- RP2040 boards (e.g. Raspberry Pi Pico / Pico W)

It is optimized for **PlatformIO + VS Code** as the primary workflow, with
`arduino-cli` support kept as an optional, CLI-friendly alternative.

You can treat this repo as a base, make a new GitHub repository from it, and
quickly get from "plug in board" → "running sketch" with minimal setup.

---

## Features

- **Ready-to-use PlatformIO config** for an Arduino Uno environment.
- **arduino-cli project config** capturing board, port, and sketch path.
- Example **Blink** sketch wired up as a starting point.
- Layout designed to be easily adapted for **Arduino AVR**, **ESP32**, and
  **RP2040** boards.

---

## Repository Layout

Key files and directories:

- `platformio.ini`  
  PlatformIO configuration. Currently set up for an **Arduino Uno** using the
  `atmelavr` platform.

- `arduino-cli.ini`  
  Simple project-local configuration for `arduino-cli`, including:
  - `fqbn` (Fully Qualified Board Name)
  - default `port`
  - `sketch` path

- `src/main.cpp`  
  PlatformIO entry point containing the Blink example (for the Uno
  environment).

- `blink/blink.ino`  
  Original Arduino sketch folder used as the source for `arduino-cli`
  compile/upload.

- `main.py`  
  Placeholder Python entry point where you can add automation scripts (for
  example, calling `arduino-cli` or PlatformIO tasks programmatically).

---

## Current Arduino Uno Setup

### PlatformIO (`platformio.ini`)

The current PlatformIO environment is:

```ini
[env:uno]
platform = atmelavr
board = uno
framework = arduino

upload_port = /dev/cu.usbserial-DN050KN9
```

With this, you can:

- **Build**: `pio run`
- **Upload**: `pio run -t upload`

from the project root.

### arduino-cli (`arduino-cli.ini`)

The `arduino-cli` configuration is:

```ini
[board]
fqbn = arduino:avr:uno
port = /dev/cu.usbserial-DN050KN9

[sketch]
path = ./blink
```

The typical workflow is:

```bash
arduino-cli core install arduino:avr          # once per machine

arduino-cli compile \
  --fqbn arduino:avr:uno \
  ./blink

arduino-cli upload \
  -p /dev/cu.usbserial-DN050KN9 \
  --fqbn arduino:avr:uno \
  ./blink
```

You can change `port`, `fqbn`, and `path` in `arduino-cli.ini` when you adapt
this template for other boards or sketches.

---

## Using This Repo as a Template

You can use this repository as a **starting point** for projects targeting
different boards.

### 1. Clone and rename

1. Clone or copy this repository into a new folder.
2. Rename the folder and optionally update this README with the new project
   name and purpose.

### 2. Add or replace sketches

- For **arduino-cli**:
  - Put your sketch in its own folder (e.g. `my-sketch/my-sketch.ino`).
  - Update `path = ./my-sketch` in `arduino-cli.ini`.

- For **PlatformIO**:
  - Replace `src/main.cpp` with your own code, or add additional source files
    under `src/`.

### 3. Adjust board configuration

#### Arduino / AVR boards (e.g. Uno, Nano, Mega)

- In `platformio.ini`, change:

  ```ini
  [env:uno]
  board = uno
  ```

  to another AVR board if needed (e.g. `nanoatmega328`, `megaatmega2560`).

- In `arduino-cli.ini`, change:

  ```ini
  [board]
  fqbn = arduino:avr:uno
  ```

  to the appropriate `fqbn` from `arduino-cli board listall`.

#### ESP32 boards

1. Install core (once):

   ```bash
   arduino-cli core install esp32:esp32
   ```

2. Update `platformio.ini` to use ESP32, e.g.:

   ```ini
   [env:esp32dev]
   platform = espressif32
   board = esp32dev
   framework = arduino
   ```

3. Update `arduino-cli.ini`:

   ```ini
   [board]
   fqbn = esp32:esp32:esp32
   port = /dev/tty.SOME_ESP32_PORT
   ```

4. Point `path` to your ESP32 sketch folder.

#### RP2040 boards (e.g. Raspberry Pi Pico / Pico W)

1. Install core (once). Example using the Arduino Mbed RP2040 core:

   ```bash
   arduino-cli core install arduino:mbed_rp2040
   ```

2. Update `platformio.ini` (example for Pico):

   ```ini
   [env:pico]
   platform = raspberrypi
   board = pico
   framework = arduino
   ```

3. Update `arduino-cli.ini` to use the correct FQBN (e.g. `arduino:mbed_rp2040:rpipico`) and port.

4. Point `path` to your RP2040 sketch folder.

---

## Recommended Workflow

### When working in VS Code / PlatformIO

1. Open the folder in VS Code.
2. Ensure the PlatformIO extension is installed.
3. Use the PlatformIO status bar / sidebar to:
   - Build (`Run` / `Build`)
   - Upload (`Upload`)
   - Monitor serial (`Monitor`)

Configuration is driven by `platformio.ini`.

### How PlatformIO knows what to upload

PlatformIO does **not** look at `.ino` folders when building. Instead, it:

- Compiles sources under `src/` (for example, `src/main.cpp`).
- Uses the **environment** you select (e.g. `env:uno`, `env:esp32dev`,
  `env:pico`) to decide:
  - Which board to target (`board = uno`, `board = esp32dev`, etc.).
  - Which upload port to use (`upload_port = ...`).

That means:

- When you run:

  ```bash
  pio run -t upload -e uno       # or esp32dev / pico
  ```

  PlatformIO uploads whatever code is currently in `src/` (typically
  `src/main.cpp`) using the settings in `[env:uno]` (or the env you chose).

- If you want to switch from a **Blink** sketch to an **OLED** sketch under
  PlatformIO, you update `src/main.cpp` (or use multiple source files and
  `#ifdef`s / different envs) rather than pointing PIO directly at
  `blink/blink.ino`.

By contrast, **arduino-cli** and the Arduino IDE think in terms of **sketch
folders**:

- The sketch is the folder (e.g. `./blink`) and the `.ino` inside it.
- When you run:

  ```bash
  arduino-cli compile --fqbn arduino:avr:uno ./blink
  arduino-cli upload -p /dev/cu.usbserial-DN050KN9 --fqbn arduino:avr:uno ./blink
  ```

  `arduino-cli` compiles and uploads the `.ino` in that folder.

This template keeps **both styles**:

- PlatformIO: primary, using `src/main.cpp` and `pio run -t upload -e <env>`.
- arduino-cli: optional, using sketch folders like `./blink`.

### When working from the terminal only

From the project root:

- **List devices**:

  ```bash
  pio device list
  ```

- **Compile and upload via PlatformIO**:

  ```bash
  pio run
  pio run -t upload
  ```

- **Compile and upload via arduino-cli** (using the info mirrored in
  `arduino-cli.ini`):

  ```bash
  arduino-cli compile --fqbn <your-fqbn> <your-sketch-path>
  arduino-cli upload -p <your-port> --fqbn <your-fqbn> <your-sketch-path>
  ```

You can adapt the `<your-fqbn>`, `<your-port>`, and `<your-sketch-path>` values
based on the board and sketch you are targeting.

---

## Notes

- The serial port (`/dev/cu.usbserial-DN050KN9` in this template) may change
  when you plug boards into different USB ports or use different devices.
  Always verify with `pio device list` or `arduino-cli board list`.
- This repo is intentionally minimal so it can serve as a clean base/template
  for many different microcontroller projects.
- The files `.windsurfrules` and `.cursorrules` provide project rules for
  AI coding assistants (Windsurf, Cursor) so they know to use PlatformIO as
  the primary workflow and keep this repo usable as a template.
- To use the serial monitor from the terminal, use:
    arduino-cli compile --fqbn arduino:avr:uno ./i2c_scanner
    arduino-cli upload -p /dev/cu.usbserial-DN050KN9 --fqbn arduino:avr:uno ./i2c_scanner
    ```bash
    screen /dev/cu.usbserial-DN050KN9 9600
  ```


  
  