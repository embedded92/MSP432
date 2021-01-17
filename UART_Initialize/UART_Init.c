/*
 * UART_Init.c
 *  Created on: 04-Mar-2018
 *      Author: Ramneet Kaur
 */


#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "UART_Init.h"
#include "string.h"
#include "stdlib.h"
/* UART configuration at 115200 Baud rate and 24MHz clock*/
const eUSCI_UART_Config uart115200_24MHz = {
EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        13,                                      // BRDIV = 13
        0,                                       // UCxBRF = 0
        37,                                      // UCxBRS = 37
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling

        };
/* UART configuration at 9600 Baud rate and 24MHz clock*/
const eUSCI_UART_Config uart9600_24MHz = {
EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        156,                                      // BRDIV = 13
        4,                                       // UCxBRF = 0
        0,                                      // UCxBRS = 37
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling

        };


/* UART configuration at 19200 Baud rate and 24MHz clock*/
const eUSCI_UART_Config uart19200_24MHz = {
EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        78,                                      // BRDIV = 13
        2,                                       // UCxBRF = 0
        0,                                      // UCxBRS = 37
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling

        };
/* UART configuration at 57600 Baud rate and 24MHz clock*/
const eUSCI_UART_Config uart57600_24MHz = {
EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        26,                                      // BRDIV = 13
        0,                                       // UCxBRF = 0
        111,                                      // UCxBRS = 37
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling

        };

void UartWrite(uint32_t UART, char str[100])
{

    int data_len = strlen(str);
    int i = 0;
    for (i = 0; i < data_len; i++)
    {
        MAP_UART_transmitData(UART, str[i]);
    }
}
void UartInit0(int baud)
{
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(
    GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    if(baud==9600)
        MAP_UART_initModule(EUSCI_A0_BASE, &uart9600_24MHz);
    else if(baud==19200)
        MAP_UART_initModule(EUSCI_A0_BASE, &uart19200_24MHz);
    else if(baud==57600)
        MAP_UART_initModule(EUSCI_A0_BASE, &uart57600_24MHz);
    else if(baud==115200)
        MAP_UART_initModule(EUSCI_A0_BASE, &uart115200_24MHz);
    MAP_UART_enableModule(EUSCI_A0_BASE);
    MAP_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA0);
}

void EUSCIA0_IRQHandler(void)
{
    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A0_BASE);

    MAP_UART_clearInterruptFlag(EUSCI_A0_BASE, status);

    if (status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        uart0rxdata = MAP_UART_receiveData(EUSCI_A0_BASE);
    }
    rx0buf[buff0Index] = uart0rxdata;
    buff0Index++;
}

void UartInit1(int baud)
{
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(
            GPIO_PORT_P2, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    if (baud == 9600)
        MAP_UART_initModule(EUSCI_A1_BASE, &uart9600_24MHz);
    else if (baud == 19200)
        MAP_UART_initModule(EUSCI_A1_BASE, &uart19200_24MHz);
    else if (baud == 57600)
        MAP_UART_initModule(EUSCI_A1_BASE, &uart57600_24MHz);
    else if (baud == 115200)
        MAP_UART_initModule(EUSCI_A1_BASE, &uart115200_24MHz);
    MAP_UART_enableModule(EUSCI_A1_BASE);
    MAP_UART_enableInterrupt(EUSCI_A1_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA1);
}



void EUSCIA1_IRQHandler(void)
{
    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A1_BASE);

    MAP_UART_clearInterruptFlag(EUSCI_A1_BASE, status);

    if (status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        uart1rxdata = MAP_UART_receiveData(EUSCI_A1_BASE);
        //MAP_UART_transmitData(EUSCI_A2_BASE, UART1RxData);
        MAP_Interrupt_disableSleepOnIsrExit();
    }
    rx1buf[buff1Index] = uart1rxdata;
    buff1Index++;
}


void UartInit2(int baud)
{
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(
    GPIO_PORT_P3, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

        if(baud==9600)
            MAP_UART_initModule(EUSCI_A2_BASE, &uart9600_24MHz);
        else if (baud == 19200)
                MAP_UART_initModule(EUSCI_A2_BASE, &uart19200_24MHz);
        else if(baud==57600)
            MAP_UART_initModule(EUSCI_A2_BASE, &uart57600_24MHz);
        else if(baud==115200)
                MAP_UART_initModule(EUSCI_A2_BASE, &uart115200_24MHz);
    MAP_UART_enableModule(EUSCI_A2_BASE);
    MAP_UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA2);
}


void EUSCIA2_IRQHandler(void)
{

    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A2_BASE);

    MAP_UART_clearInterruptFlag(EUSCI_A2_BASE, status);

    if (status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        uart2rxdata = MAP_UART_receiveData(EUSCI_A2_BASE);
        MAP_Interrupt_disableSleepOnIsrExit();
    }
   // MAP_UART_transmitData(EUSCI_A2_BASE, UART2RxData);
    rx2buf[buff2Index] = uart2rxdata;
    buff2Index++;

}
void UartInit3(int baud)
{
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(
            GPIO_PORT_P9, GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
    if (baud == 9600)
        MAP_UART_initModule(EUSCI_A3_BASE, &uart9600_24MHz);
    else if (baud == 19200)
        MAP_UART_initModule(EUSCI_A3_BASE, &uart19200_24MHz);
    else if (baud == 57600)
        MAP_UART_initModule(EUSCI_A3_BASE, &uart57600_24MHz);
    else if (baud == 115200)
        MAP_UART_initModule(EUSCI_A3_BASE, &uart115200_24MHz);
    MAP_UART_enableModule(EUSCI_A3_BASE);
    MAP_UART_enableInterrupt(EUSCI_A3_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA3);
}


void EUSCIA3_IRQHandler(void)
{

    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A3_BASE);

    MAP_UART_clearInterruptFlag(EUSCI_A3_BASE, status);

    if (status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        uart3rxdata = MAP_UART_receiveData(EUSCI_A3_BASE);
        MAP_Interrupt_disableSleepOnIsrExit();
    }
    rx3buf[buff3Index] = uart3rxdata;
    buff3Index++;
    //MAP_UART_transmitData(EUSCI_A2_BASE, UART3RxData);
}
