#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include "UART_Init.h"
int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();
    /* Setting DCO to 24MHz (upping Vcore) */
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);
    uart0Init(115200);
    uart1Init(9600);
    uartPrint(EUSCI_A0_BASE, "Hello World from UART0 at 115200 baud rate");
    uartPrint(EUSCI_A1_BASE, "HEllo World from UART1 at 9600 baud rate");

}
