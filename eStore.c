#include "eStore.h"

const char * TAG_STORE = "STORE";

void estore_init() {
    esp_err_t ret = nvs_flash_init();
    
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGW(TAG_STORE,"Reboot Flash");
        ESP_ERROR_CHECK(nvs_flash_erase());  
        ret = nvs_flash_init();                      
    }
    ESP_ERROR_CHECK(ret);
}

esp_err_t estore_open_nvs(nvs_handle_t *nvs_handle) {
    return nvs_open("storage", NVS_READWRITE, nvs_handle);
}

void estore_close_nvs(nvs_handle_t nvs_handle) {
    nvs_close(nvs_handle);
}

void estore_write_bool(const char* name, bool value) {
    nvs_handle_t nvs_handle;
    
    esp_err_t err = estore_open_nvs(&nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG_STORE, "Error at open NVS: %s", esp_err_to_name(err));
        return;
    }

    err = nvs_set_u8(nvs_handle, name, value);
    if (err != ESP_OK) 
        ESP_LOGE(TAG_STORE, "Error at Save: %s", esp_err_to_name(err));

    err = nvs_commit(nvs_handle);
    if (err != ESP_OK) 
        ESP_LOGE(TAG_STORE, "Error in Commit: %s", esp_err_to_name(err));
    
    estore_close_nvs(nvs_handle);
}

void estore_write_int8(const char* name, int8_t value) {
    nvs_handle_t nvs_handle;
    
    esp_err_t err = estore_open_nvs(&nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG_STORE, "Error at open NVS: %s", esp_err_to_name(err));
        return;
    }

    err = nvs_set_i8(nvs_handle, name, value);
    if (err != ESP_OK)
        ESP_LOGE(TAG_STORE, "Error at Save: %s", esp_err_to_name(err));
    else {
        err = nvs_commit(nvs_handle);
        if (err != ESP_OK)
            ESP_LOGE(TAG_STORE, "Error in Commit: %s", esp_err_to_name(err));
    }
    
    estore_close_nvs(nvs_handle);
}

void estore_write_int32(const char* name, int32_t value) {
    nvs_handle_t nvs_handle;
    
    esp_err_t err = estore_open_nvs(&nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG_STORE, "Error at open NVS: %s", esp_err_to_name(err));
        return;
    }

    err = nvs_set_i32(nvs_handle, name, value);
    if (err != ESP_OK)
        ESP_LOGE(TAG_STORE, "Error at Save: %s", esp_err_to_name(err));
    else {
        err = nvs_commit(nvs_handle);
        if (err != ESP_OK)
            ESP_LOGE(TAG_STORE, "Error in Commit: %s", esp_err_to_name(err));
    }
    
    estore_close_nvs(nvs_handle);
}

void estore_write_string(const char* name, const char* value) {
    nvs_handle_t nvs_handle;

    esp_err_t err = estore_open_nvs(&nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG_STORE, "Error at open NVS: %s", esp_err_to_name(err));
        return;
    }

    err = nvs_set_str(nvs_handle, name, value);
    if (err != ESP_OK)
        ESP_LOGE(TAG_STORE, "Error at Save: %s", esp_err_to_name(err));
    else {
        err = nvs_commit(nvs_handle);
        if (err != ESP_OK) 
            ESP_LOGE(TAG_STORE, "Error in Commit: %s", esp_err_to_name(err));
    }

    estore_close_nvs(nvs_handle);
}

esp_err_t estore_write_struct(const char* name, const void* _struct,size_t size){
    nvs_handle_t nvs_handle;

    esp_err_t err = estore_open_nvs(&nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG_STORE, "Error at open NVS: %s", esp_err_to_name(err));
        return err;
    }
    err = nvs_set_blob(nvs_handle, name, _struct, size);
    if (err == ESP_OK) 
        err = nvs_commit(nvs_handle);

    nvs_close(nvs_handle);
    return err;

}

bool estore_read_struct(const char* name , void * _struct , size_t size) {
    nvs_handle_t nvs_handle;
    esp_err_t err;
    err = estore_open_nvs(&nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG_STORE, "Error at open NVS: %s", esp_err_to_name(err));
        return false;
    }
    bool to_return = true;
    err = nvs_get_blob(nvs_handle, name, _struct, &size);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGW(TAG_STORE, "Key dont found: %s", name);
        to_return = false;
    } else if (err != ESP_OK) {
        ESP_LOGE(TAG_STORE, "Error: %s", esp_err_to_name(err));
        to_return = false;
    }
    
    nvs_close(nvs_handle);
    return to_return;
}

void estore_write_uint64(const char* name, uint64_t value) {
    nvs_handle_t nvs_handle;
    
    esp_err_t err = estore_open_nvs(&nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG_STORE, "Error at open NVS: %s", esp_err_to_name(err));
        return;
    }

    err = nvs_set_u64(nvs_handle, name, value);
    if (err != ESP_OK)
        ESP_LOGE(TAG_STORE, "Error at Save: %s", esp_err_to_name(err));
    else {
        err = nvs_commit(nvs_handle);
        if (err != ESP_OK)
            ESP_LOGE(TAG_STORE, "Error in Commit: %s", esp_err_to_name(err));
    }

    estore_close_nvs(nvs_handle);
}

void estore_write_float(const char* name, float value) {
    nvs_handle_t nvs_handle;
    esp_err_t err;
    
    err = estore_open_nvs(&nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG_STORE, "Error at open NVS: %s", esp_err_to_name(err));
        return;
    }

    uint32_t value_as_int;
    memcpy(&value_as_int, &value, sizeof(value_as_int));

    err = nvs_set_u32(nvs_handle, name, value_as_int);
    if (err != ESP_OK)
        ESP_LOGE(TAG_STORE, "Error at Save: %s", esp_err_to_name(err));
    else {
        err = nvs_commit(nvs_handle);
        if (err != ESP_OK) 
            ESP_LOGE(TAG_STORE, "Error in Commit: %s", esp_err_to_name(err));
    }

    estore_close_nvs(nvs_handle);
}

bool estore_read_int32(const char* name, int32_t* value) {
    nvs_handle_t nvs_handle;
    esp_err_t err = estore_open_nvs(&nvs_handle);
    
    if (err != ESP_OK) {
        ESP_LOGE(TAG_STORE, "Error at open NVS: %s", esp_err_to_name(err));
        return false;
    }

    err = nvs_get_i32(nvs_handle, name, value);
    estore_close_nvs(nvs_handle);

    if (err == ESP_OK) return true;
    
    if (err == ESP_ERR_NVS_NOT_FOUND)
        ESP_LOGW(TAG_STORE, "Value %s not Found\n", name);
    else
        ESP_LOGE(TAG_STORE, "Error at read value: %s", esp_err_to_name(err));
    
    return false;
}

bool estore_read_int8(const char* name, int8_t* value) {
    nvs_handle_t nvs_handle;
    esp_err_t err = estore_open_nvs(&nvs_handle);
    
    if (err != ESP_OK) {
        ESP_LOGE(TAG_STORE, "Error at open NVS: %s", esp_err_to_name(err));
        return false;
    }
    err = nvs_get_i8(nvs_handle, name, value);
    estore_close_nvs(nvs_handle);

    if (err == ESP_OK) return true;
    
    if (err == ESP_ERR_NVS_NOT_FOUND)
        ESP_LOGW(TAG_STORE, "Value %s not Found\n", name);
    else
        ESP_LOGE(TAG_STORE, "Error at read value: %s", esp_err_to_name(err));
    
    return false;
}

bool estore_read_uint64(const char* name, uint64_t* value) {
    nvs_handle_t nvs_handle;
    esp_err_t err = estore_open_nvs(&nvs_handle);
    
    if (err != ESP_OK) {
        ESP_LOGE(TAG_STORE, "Error at open NVS: %s", esp_err_to_name(err));
        return false;
    }

    err = nvs_get_u64(nvs_handle, name, value);
    estore_close_nvs(nvs_handle);

    if (err == ESP_OK) return true;

    if (err == ESP_ERR_NVS_NOT_FOUND)
        ESP_LOGW(TAG_STORE, "Value %s not Found\n", name);
    else
        ESP_LOGE(TAG_STORE, "Error at read value: %s", esp_err_to_name(err));
    
    return false;
}

bool estore_read_float(const char* name, float* value) {
    nvs_handle_t nvs_handle;
    esp_err_t err = estore_open_nvs(&nvs_handle);
    
    if (err != ESP_OK) {
        ESP_LOGE(TAG_STORE, "Error at open NVS: %s", esp_err_to_name(err));
        return false;
    }

    uint32_t value_as_int;
    err = nvs_get_u32(nvs_handle, name, &value_as_int);
    estore_close_nvs(nvs_handle);

    if (err == ESP_OK) {
        memcpy(value, &value_as_int, sizeof(value_as_int));
        return true;
    }
    
    if (err == ESP_ERR_NVS_NOT_FOUND)
        ESP_LOGW(TAG_STORE, "Value not found: %s", name);
    else
        ESP_LOGE(TAG_STORE, "Error at Read: %s", esp_err_to_name(err));
    
    return false;
}

bool estore_read_string(const char* name, char* buffer, size_t buffer_size) {
    nvs_handle_t nvs_handle;
    esp_err_t err = estore_open_nvs(&nvs_handle);

    if (err != ESP_OK) {
        ESP_LOGE(TAG_STORE, "Error at open NVS: %s", esp_err_to_name(err));
        return false;
    }

    err = nvs_get_str(nvs_handle, name, buffer, &buffer_size);
    estore_close_nvs(nvs_handle);

    if (err == ESP_OK) return true;

    if (err == ESP_ERR_NVS_NOT_FOUND)
        ESP_LOGW(TAG_STORE, "Key dont found: %s", name);
    else
        ESP_LOGE(TAG_STORE, "Error: %s", esp_err_to_name(err));

    return false;
}

void estore_read_or_write_struct(const char* _name , void * _struct , size_t size , void * _default){
    if(!estore_read_struct(_name,_struct,size)){
        _struct = _default;
        estore_write_struct(_name,_struct,size);
    }

}


void estore_read_or_write_int8(const char* _name , int8_t* _value , int8_t _default){
    if(!estore_read_int8(_name,_value)){
        *_value = _default;
        estore_write_int8(_name,*_value);
    }
}
