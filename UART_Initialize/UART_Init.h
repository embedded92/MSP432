/*
 * Initialize the corresponding UART using the uartXInit(baud)function
 * the received data will be saved in rxXbuf
 * where x stands for the uartNo.
 * baud stands for baud rate of the device
 * eg. uart0Init(115200) and rx0buf
 * to print on a uart device uartPrint()
 */


#ifndef UART_INIT_H_
#define UART_INIT_H_
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

volatile uint8_t UART0RxData;
volatile uint8_t UART0TxData;
volatile uint8_t UART1RxData;
volatile uint8_t UART1TxData;
volatile uint8_t UART2RxData;
volatile uint8_t UART2TxData;
volatile uint8_t UART3RxData;
volatile uint8_t UART3TxData;
char rx0buf[128];
char rx1buf[128];
char rx2buf[128];
char rx3buf[128];
int buff0Index;
int buff1Index;
int buff2Index;
int buff3Index;
void uart0Init(int baud);
void uart1Init(int baud);
void uart2Init(int baud);
void uart3Init(int baud);
void uartPrint(uint32_t UART, char str[100]);
#endif
