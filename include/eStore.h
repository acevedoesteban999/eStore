#pragma once

#include "nvs_flash.h"
#include "esp_err.h"
#include "esp_log.h"
#include <string.h>

extern const char * TAG_STORE;  // Declaración de la constante externa

void init_nvs(void);
esp_err_t open_nvs_handle(nvs_handle_t *nvs_handle);
void write_bool_in_nvs(const char *name, bool value);
void write_int8_in_nvs(const char* name, int8_t value);
void write_uint64_in_nvs(const char* name, uint64_t value);
void write_float_in_nvs(const char* name, float value);
void write_string_in_nvs(const char* name, const char* value);
esp_err_t write_struct_in_nvs(const char* name, const void* _struct,size_t size);
void *read_struct_from_nvs(const char *name, const void *_struct, size_t size);
int8_t read_i8_from_nvs(const char *name);
float read_float_from_nvs(const char* name);