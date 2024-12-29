#pragma once

#include "nvs_flash.h"
#include "esp_err.h"
#include "esp_log.h"
#include <string.h>

extern const char * TAG_STORE;  // Declaración de la constante externa

void estore_init(void);
esp_err_t estore_open_nvs(nvs_handle_t *nvs_handle);
void estore_write_bool(const char *name, bool value);
void estore_write_int8(const char* name, int8_t value);
void estore_write_uint64(const char* name, uint64_t value);
void estore_write_float(const char* name, float value);
void estore_write_string(const char* name, const char* value);
esp_err_t estore_write_struct(const char* name, const void* _struct,size_t size);
bool estore_read_struct(const char *name, void *_struct, size_t size);
int8_t estore_read_i8(const char *name);
float estore_read_float(const char* name);