#include "driver/uart.h"
#include "esp_log.h"
#include <string.h>
#include "driver/lp_io.h"


#define UART_PORT_NUM      UART_NUM_2  // Use UART0 (connected to USB)
#define UART_BAUD_RATE     9600
#define BUF_SIZE           1024
#define OUTPUT1 GPIO_NUM_2


void app_main(void) {
    // Configure UART parameters
    const uart_config_t uart_config = {
        .baud_rate = UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    gpio_set_direction(OUTPUT1, GPIO_MODE_OUTPUT);
    gpio_set_level(OUTPUT1,1);

    uart_param_config(UART_PORT_NUM, &uart_config);
    uart_set_pin(UART_PORT_NUM, GPIO_NUM_17, GPIO_NUM_16, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_PORT_NUM, BUF_SIZE, BUF_SIZE, 0, NULL, 0);
    // Loop to send and receive data
    uint8_t data[BUF_SIZE];
    while (1) {
        // Send data to PC
        const char *message = "\x01";
        uart_write_bytes(UART_PORT_NUM, message, strlen(message));
        
        // Read data from PC
        //  int length = uart_read_bytes(UART_PORT_NUM, data, BUF_SIZE, 100 / portTICK_PERIOD_MS);
        //  if (length > 0) {
        //      data[length] = '\0';  // Null-terminate received string
        //      ESP_LOGI("UART", "Received: %s", data);
        //     char DATA[length];
        //     for(int i=0; i<=length;i++){
        //         DATA[i]=data[i];
        //     }
        //     ESP_LOGI("UART_DATA", "Received: %s", DATA);
        //     if(!strcmp(DATA,"Start")){
        //         gpio_set_level(OUTPUT1,1);
        //         ESP_LOGE("UART","START");
        //     } 
        //     else if ( !strcmp(DATA,"Stop")){
        //         gpio_set_level(OUTPUT1,0);
        //         ESP_LOGE("UART","STOP");
        //         }
        //     else{
        //         ESP_LOGE("UART","no data received");                
        //     }

                
        //}

        vTaskDelay(1000 / portTICK_PERIOD_MS);  // Delay 1 second
    }
}
