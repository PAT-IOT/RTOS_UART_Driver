# UART Communication Example with FreeRTOS on ESP32

## Description
This example demonstrates how data is transmitted and received over UART using FreeRTOS tasks on an ESP32 device. When the user writes the message "this is user message" through the serial interface, the program waits for a delay period of 5 seconds before reading the incoming data. Upon reading the data, it outputs the number of bytes received followed by the received message.

## Serial Output
69

70

71

Read 20 bytes: this is user message

72

73

74


In the example above:
- The numbers 69, 70, and 71 represent some other activity or output before receiving the message.
- "Read 20 bytes" indicates that 20 bytes of data have been received.
- "this is user message" is the actual message received from the user.
- The numbers 72, 73, and 74 represent some subsequent activity or output after receiving the message.

## Code Overview
This project consists of two tasks:
1. **tx_task**: This task continuously transmits data over UART.
2. **rx_task**: This task reads data from UART and prints it to the Serial interface. It waits for 5 seconds between successive reads.

## Usage
- Connect your ESP32 device to a computer via USB.
- Open a serial terminal (e.g., Arduino Serial Monitor) with the appropriate baud rate (115200).
- Upload the code to your ESP32 device.
- After uploading, you should see the UART output on the serial terminal.
