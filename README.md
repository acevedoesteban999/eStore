# eStore

The eStore module is an implementation for handling non-volatile storage (NVS) on the ESP32. This module allows you to read and write various types of data to the NVS.

## Features

- Initialize NVS.
- Read and write boolean values.
- Read and write 8-bit integers.
- Read and write 64-bit integers.
- Read and write strings.
- Read and write float values.
- Read and write custom structures.

## Main Functions

- `void estore_init()`: Initializes the NVS.
- `void estore_write_bool(const char* name, bool value)`: Writes a boolean value to NVS.
- `void estore_write_int8(const char* name, int8_t value)`: Writes an 8-bit integer to NVS.
- `void estore_write_uint64(const char* name, uint64_t value)`: Writes a 64-bit integer to NVS.
- `void estore_write_string(const char* name, const char* value)`: Writes a string to NVS.
- `void estore_write_float(const char* name, float value)`: Writes a float value to NVS.
- `esp_err_t estore_write_struct(const char* name, const void* _struct, size_t size)`: Writes a custom structure to NVS.
- `bool estore_read_struct(const char* name, void* _struct, size_t size)`: Reads a custom structure from NVS.
- `void estore_read_string(const char* name, char* buffer, size_t buffer_size)`: Reads a string from NVS.
- `int8_t estore_read_i8(const char* name)`: Reads an 8-bit integer from NVS.
- `uint64_t estore_read_uint64(const char* name)`: Reads a 64-bit integer from NVS.
- `float estore_read_float(const char* name)`: Reads a float value from NVS.

## Example Usage

```c
#include "eStore.h"

void app_main() {
    // Initialize NVS
    estore_init();

    // Write a boolean value to NVS
    estore_write_bool("example_bool", true);

    // Read a boolean value from NVS
    bool example_bool = read_bool_from_nvs("example_bool");
    printf("Read boolean value: %d\n", example_bool);

    // Write a string to NVS
    estore_write_string("example_string", "Hello, NVS!");

    // Read a string from NVS
    char buffer[20];
    estore_read_string("example_string", buffer, sizeof(buffer));
    printf("Read string value: %s\n", buffer);
}
