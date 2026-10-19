# LEDy – ESP32-based smart floorlamp upgrade

## Description
LEDy is a hardware project designed to integrate old LED strips into the Apple HomeKit system. It uses the ESP32 microcontroller with the HomeSpan library for the Arduino framework. It supports existing hardware buttons and capacitive sensors, allowing control over brightness and on/off state for LED strips or any other 12V load.
The project consists of two parts: code and hardware. A Gerber file for the custom PCB is included. The PCB form factor is based on the physical dimensions of the original floorlamp housing but can be reused in other compact devices, as the PCB width matches the ESP32 chip.

## ESP32 and hardware
ESP32 is the core of the whole system. Thanks to the large community, Arduino support, simple networking setup, and low cost, it's the most suitable MCU for small IoT projects. The system was tested both on a dev board and on a custom PCB designed specifically for this project.
LED dimming is done via PWM through a MOSFET transistor. The control button is implemented as a capacitive sensor and needs to be tuned empirically depending on the circuit (more on this in the `main.cpp` section).

## platformio.ini
The project requires specific settings for ESP32 in the `platformio.ini` file to avoid compilation and firmware upload errors.

## HomeSpan
[HomeSpan](https://github.com/HomeSpan/HomeSpan) is a popular open-source library for ESP32 + Arduino to integrate with Apple HomeKit. For updates or custom logic, check the official documentation and examples — they’re great. This project is based on the Dimmable LED example.
** After the first flash, Wi-Fi credentials must be entered via Serial Monitor. ** For the initial connection, refer to the HomeSpan docs. Default pairing code is: **466-37-726**

## Capacitive sensor
The pin should be set manually in main.cpp, according to the ESP32 datasheet. After uploading the firmware, ESP32 starts printing raw capacitive values to the Serial Monitor.
### To define a proper threshold:
- Note the value when not touching the sensor,
- Then note the value when touching it,
- Set your threshold somewhere between those two values.

## main.cpp
The `setup()` function handles initial library setup and MCU configuration. The Serial Monitor is used for debugging, Wi-Fi setup, and status output.
The `loop()` function constantly checks the state of the capacitive button and runs `homeSpan.poll()`

## DEV_LED.h
All accessory-related logic is handled here, based on HomeSpan's structure.
`update()` — modified from HomeSpan's original to handle smooth dimming using global variables.
`touch()` — handles capacitive sensor input and syncs it with the update() function.
This setup ensures that any change made by physical input is reflected in the HomeKit app and vice versa. Global variables for power and brightness levels help maintain the last known state across different control methods.

## level_adjust()
HomeSpan controls power via 1/0 logic and brightness through PWM. But real-world LED brightness jumps harshly without smoothing.
This function introduces a 10 ms delay between the current and target brightness levels (coming from HomeKit). This creates a soft dimming effect when turning on/off, whether controlled from the app or via the capacitive button.

## Gerber files
Includes a custom PCB designed mostly with through-hole (THT) components. The ESP32 is the only part that needs SMD soldering. Power is handled via a prebuilt MP1584 module.

## Electrical characteristics
Tested with a 1-meter LED strip using a 12V / 1A power supply.

## Future improvements
- Replace button polling with proper interrupt-based input
- Add support for 3 MOSFETs to control RGB LED strips


