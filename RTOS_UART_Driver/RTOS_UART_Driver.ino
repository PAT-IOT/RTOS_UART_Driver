//  Description
// This example demonstrates how data is transmitted and received over UART using FreeRTOS tasks 
// on an ESP32 device. When the user writes the message "this is user message" through the
// serial interface, the program waits for a delay period of 5 seconds before reading the incoming data. 
// Upon reading the data, it outputs the number of bytes received followed by the received message.

// ### Serial Output
// 69
// 70
// 71
// Read 20 bytes: this is user message
// 72
// 73
// 74



#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"

#define TXD_PIN (GPIO_NUM_1)
#define RXD_PIN (GPIO_NUM_3)
//________________________________________________________________________________________________________________
// Task to transmit data over UART
static void tx_task(void *arg) {
  int i = 0;
  char buffer[16];  // Buffer to hold the string representation of the integer
  while (1) {
    i++;
    // Convert integer to string
    snprintf(buffer, sizeof(buffer), "%d\n", i);  // Convert integer to string
    // Send the string via UART
    uart_write_bytes(UART_NUM_0, buffer, strlen(buffer));  
    vTaskDelay(1000 / portTICK_PERIOD_MS);                
  }
}
//________________________________________________________________________________________________________________
static const int RX_BUF_SIZE = 1024;
static void rx_task(void *arg) {
  uint8_t *data = (uint8_t *)malloc(RX_BUF_SIZE + 1);
  while (1) {
    //--------------------------------------------------
    // Read data from UART
    const int rxBytes = uart_read_bytes(UART_NUM_0, data, RX_BUF_SIZE, 1 / portTICK_RATE_MS);// 1ms for waitting
    if (rxBytes > 0) {
      data[rxBytes] = 0;  // Null-terminate the received data                    
      Serial.println("Read " + String(rxBytes) + " bytes: " + ((char *)data));   // Print received data
      //uart_write_bytes(UART_NUM_0, (char *)data, strlen((char *)data));        // Using uart_write_bytes function for transmitting data is more efficient than using Serial.print
    }
    vTaskDelay(5000 / portTICK_PERIOD_MS);  // Delay before reading next data
    //--------------------------------------------------
  }
  free(data);  // Free allocated memory for data buffer
}
//________________________________________________________________________________________________________________
void setup() {
  Serial.begin(115200);
  // Configure UART parameters
  const uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
  };
  // Install UART driver with buffer for received data
  uart_driver_install(UART_NUM_0, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
  uart_param_config(UART_NUM_0, &uart_config);
  uart_set_pin(UART_NUM_0, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

  // Create tasks for receiving and transmitting data
  xTaskCreatePinnedToCore(rx_task, "uart_rx_task", 1024 * 2, NULL, configMAX_PRIORITIES, NULL, 1);
  xTaskCreatePinnedToCore(tx_task, "uart_tx_task", 1024 * 2, NULL, configMAX_PRIORITIES - 1, NULL, 0);
}
//________________________________________________________________________________________________________________
void loop() {
}



