/*
//slave
#include <stdio.h>
#include "driver/i2c.h"
#include "esp_log.h"

#define I2C_SLAVE_NUM         I2C_NUM_1        // I2C port number for slave
#define I2C_SLAVE_SCL_IO      22               // GPIO number for I2C SCL
#define I2C_SLAVE_SDA_IO      21               // GPIO number for I2C SDA
#define I2C_SLAVE_ADDR        0x58             // Slave address (7-bit)
#define I2C_SLAVE_RX_BUF_LEN  128              // Receive buffer size
#define I2C_SLAVE_TX_BUF_LEN  128              // Transmit buffer size

static const char *TAG = "I2C_Slave";

// Function to initialize ESP32 as I2C Slave
void i2c_slave_init() {
    i2c_config_t conf = {
        .sda_io_num = I2C_SLAVE_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_SLAVE_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .mode = I2C_MODE_SLAVE,
        .slave = {
            .addr_10bit_en = 0,  // Use 7-bit addressing
            .slave_addr = I2C_SLAVE_ADDR,
        },
    };

    i2c_param_config(I2C_SLAVE_NUM, &conf);
    i2c_driver_install(I2C_SLAVE_NUM, conf.mode, I2C_SLAVE_RX_BUF_LEN, I2C_SLAVE_TX_BUF_LEN, 0);
    ESP_LOGI(TAG, "I2C slave initialized at address 0x%02x", I2C_SLAVE_ADDR);
}

void app_main() {
    // Initialize the I2C slave
    i2c_slave_init();

    uint8_t data[128];  // Buffer to receive data

    while (1) {
        // Read data sent by the I2C master
        int size = i2c_slave_read_buffer(I2C_SLAVE_NUM, data, sizeof(data), 1000 / portTICK_PERIOD_MS);

        if (size > 0) {
            ESP_LOGI(TAG, "Received data from master: ");
            for (int i = 0; i < size; i++) {
                printf("0x%02x ", data[i]);  // Print received bytes
            }
            printf("\n");
        } else {
            ESP_LOGW(TAG, "No data received within timeout");
        }
    }
}*/

/*
//master
#include "driver/i2c.h"
#include "esp_log.h"

#define I2C_MASTER_NUM       I2C_NUM_0         // I2C port number for master
#define I2C_MASTER_SCL_IO    22                // GPIO number for I2C SCL
#define I2C_MASTER_SDA_IO    21                // GPIO number for I2C SDA
#define I2C_MASTER_FREQ_HZ   100000            // I2C master clock frequency (100kHz)
#define I2C_SLAVE_ADDR       0x58              // I2C slave address (7-bit)

// Function to initialize ESP32 as I2C Master
void i2c_master_init() {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
}

// Function to send data from master to slave
void i2c_master_send_data(uint8_t *data, size_t length) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);  // Start I2C command
    i2c_master_write_byte(cmd, (I2C_SLAVE_ADDR << 1) | I2C_MASTER_WRITE, true);  // Send slave address and write bit
    i2c_master_write(cmd, data, length, true);  // Send the data
    i2c_master_stop(cmd);  // Stop the I2C command
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);  // Execute command
    if (ret == ESP_OK) {
        ESP_LOGI("I2C_Master", "Data sent successfully");
    } else {
        ESP_LOGE("I2C_Master", "Failed to send data");
    }
    i2c_cmd_link_delete(cmd);  // Clean up
}

void app_main() {
    // Initialize the I2C master
    i2c_master_init();

    uint8_t data[] = "DALI";  // Example data to send to slave

    while (1) {
        // Send data to the slave
        i2c_master_send_data(data, sizeof(data));
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // Delay 1 second before sending again
    }
}*/

