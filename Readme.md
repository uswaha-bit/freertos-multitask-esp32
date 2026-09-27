# FreeRTOS Multi-Task LED Demo (ESP32)

A simulated embedded systems project demonstrating real FreeRTOS task scheduling on the ESP32, built and run entirely in the [Wokwi](https://wokwi.com) online simulator.

**This project was developed and tested in simulation (Wokwi), not on physical hardware.**

## What it does

Two independent FreeRTOS tasks run concurrently on the ESP32:
- `fastBlinkTask` toggles an LED every 200ms
- `slowBlinkTask` toggles a second LED every 1000ms

Both tasks are created with equal priority via `xTaskCreate`, and neither blocks the other — this demonstrates the FreeRTOS scheduler genuinely time-slicing between two independent execution contexts, rather than simple sequential delay-based blinking in a single loop.

## Why this project

The goal was to get hands-on with FreeRTOS task management on the ESP32 — creating tasks, understanding priorities, and seeing real concurrent scheduling in action, which is foundational to real-time embedded systems work.

## Tech

- ESP32 (simulated)
- Arduino framework for ESP32 (which runs on top of the same real FreeRTOS used in ESP-IDF)
- FreeRTOS task scheduling (`xTaskCreate`, `vTaskDelay`)
- Wokwi simulation

## How to run this yourself

1. Go to [wokwi.com](https://wokwi.com) and create a new ESP32 project
2. Replace the contents of `main.cpp` (or `sketch.ino`, depending on the template) with the code in this repo
3. Replace `diagram.json` with the one in this repo (defines an ESP32 board wired to two LEDs on GPIO 2 and GPIO 4)
4. Click the Play button to build and simulate

## A note on the development process

The first version of this project targeted raw ESP-IDF directly, but Wokwi's browser-based project template turned out to build against the **Arduino framework** for ESP32, which has its own `main.cpp` entry point wrapping `setup()`/`loop()`. Getting this working involved resolving a few real build issues:
- A duplicate `app_main()` definition conflict (raw ESP-IDF code vs. the framework's own entry point)
- A C-vs-C++ linkage mismatch (`Serial` and mangled `setup()`/`loop()` symbols requiring the file to be compiled as `.cpp`, not `.c`)

I'm noting this because debugging build/toolchain issues like these is a real, transferable embedded development skill, not just "writing code that works on the first try."

## What I'd do with physical hardware

- Verify actual GPIO drive characteristics and confirm LED timing matches the simulation
- Add a hardware interrupt-driven button to demonstrate task synchronization (e.g. a semaphore triggered from an ISR)
- Try the same task logic in a real ESP-IDF project (not the Arduino framework) to compare directly against raw `xTaskCreate` in a non-Arduino environment