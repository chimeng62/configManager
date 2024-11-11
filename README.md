# ConfigManager Library

The **ConfigManager** library is a lightweight and user-friendly configuration manager designed for Arduino-based projects. It allows for the easy storage and management of configuration settings on the device, using JSON format. ConfigManager leverages the LittleFS file system to persist configuration data and supports common data types like `int`, `double`, `bool`, `String`, and `const char*`.

## Features

- **Persistent Configuration Storage**: Stores configuration settings in a JSON file on LittleFS.
- **Type-Safe Configuration Management**: Supports `double`, `int`, `bool`, `String`, and `const char*` data types.
- **Dynamic Setting of Configurations**: Allows you to set and update configuration values at runtime.
- **Debugging Support**: Includes a `printConfig` function to output the configuration settings for debugging.

## Requirements

- **Arduino** platform.
- **ArduinoJson** library for JSON parsing and serialization.
- **LittleFS** library for file system management.

## Installation

1. Clone or download the repository into your Arduino libraries directory.
2. Ensure **ArduinoJson** and **LittleFS** are installed via the Arduino Library Manager.

## Usage

See example code
