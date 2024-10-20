
//master
#include <stdio.h>
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define PIN_NUM_MISO 19  // Master In Slave Out
#define PIN_NUM_MOSI 23  // Master Out Slave In
#define PIN_NUM_CLK  18  // Clock pin
#define PIN_NUM_CS   5   // Chip select

static const char *TAG = "SPI_Master";

// SPI Master initialization
void spi_master_init(spi_device_handle_t *spi) {
    // SPI bus configuration
    spi_bus_config_t buscfg = {
        .miso_io_num = PIN_NUM_MISO,
        .mosi_io_num = PIN_NUM_MOSI,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
    };

    // Initialize the SPI bus
    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO));

    // SPI device configuration (the slave you're communicating with)
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 1 * 500 * 1000,  // Clock out at 1 MHz
        .mode = 0,                          // SPI mode 0 (CPOL=0, CPHA=0)
        .spics_io_num = PIN_NUM_CS,         // CS pin
        .queue_size = 1,                    // Transaction queue size
    };

    // Attach the slave to the SPI bus
    ESP_ERROR_CHECK(spi_bus_add_device(SPI2_HOST, &devcfg, spi));
}

// Function to send data over SPI
void spi_master_send(spi_device_handle_t spi, uint8_t *data, size_t len) {
    spi_transaction_t t = {
        .length = len * 8,  // Data length in bits
        .tx_buffer = data,  // Pointer to data to send
    };

    // Perform the SPI transaction
    esp_err_t ret = spi_device_transmit(spi, &t);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Data sent successfully");
    } else {
        ESP_LOGE(TAG, "Failed to send data");
    }
}

void app_main() {
    spi_device_handle_t spi;
    
    // Initialize SPI master
    spi_master_init(&spi);

    uint8_t data[] = "Hello";  // Example data to send

    while (1) {
        // Send data to the slave
        spi_master_send(spi, data, sizeof(data));
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // Delay for 1 second
    }
}


/*
//slave
#include <stdio.h>
#include "driver/spi_slave.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define PIN_NUM_MISO 19  // Master In Slave Out
#define PIN_NUM_MOSI 23  // Master Out Slave In
#define PIN_NUM_CLK  18  // Clock pin
#define PIN_NUM_CS   5   // Chip select

static const char *TAG = "SPI_Slave";

// SPI Slave initialization
void spi_slave_init() {
    // Configuration for the SPI bus
    spi_bus_config_t buscfg = {
        .miso_io_num = PIN_NUM_MISO,
        .mosi_io_num = PIN_NUM_MOSI,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
    };

    // Configuration for the SPI slave interface
    spi_slave_interface_config_t slvcfg = {
        .spics_io_num = PIN_NUM_CS,
        .flags = 0,
        .queue_size = 1,
        .mode = 0,  // SPI mode 0 (CPOL=0, CPHA=0)
    };

    // Initialize the SPI slave interface
    ESP_ERROR_CHECK(spi_slave_initialize(SPI2_HOST, &buscfg, &slvcfg, SPI_DMA_CH_AUTO));
}

// Function to receive data from the SPI master
void spi_slave_receive() {
    uint8_t recv_buf[128];  // Buffer to store received data
    uint8_t send_buf[128] = {0};  // Buffer to send zeros back on MISO

    spi_slave_transaction_t t = {
        .length = sizeof(recv_buf) * 8,  // Data length in bits
        .rx_buffer = recv_buf,           // Pointer to receive buffer
        .tx_buffer = recv_buf,           // Send zeros back on MISO
    };

    // Wait for the SPI transaction from the master
    esp_err_t ret = spi_slave_transmit(SPI2_HOST, &t, portMAX_DELAY);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Data received from master: ");
        printf("%s",recv_buf);
        printf("\n");
    } else {
        ESP_LOGE(TAG, "Failed to receive data");
    }
}

void app_main() {
    // Initialize SPI slave
    spi_slave_init();

    while (1) {
        // Wait to receive data from the SPI master
        spi_slave_receive();
    }
}
*/
