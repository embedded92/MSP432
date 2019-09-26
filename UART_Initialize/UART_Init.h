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
volatile uint8_t uart0rxdata;
volatile uint8_t uart1rxdata;
volatile uint8_t uart2rxdata;
volatile uint8_t uart3rxdata;
char rx0buf[128];
char rx1buf[128];
char rx2buf[128];
char rx3buf[128];
int buff0Index;
int buff1Index;
int buff2Index;
int buff3Index;
void UartInit0(int baud);
void UartInit1(int baud);
void UartInit2(int baud);
void UartInit3(int baud);
void UartWrite(uint32_t UART, char str[100]);
#endif
