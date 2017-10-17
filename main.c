#include <string.h>

#include "stm32f4xx.h"
#include "firmware.h"
#include "led.h"
#include "sd.h"
#include "ff.h"
#include "FreeRTOS.h"
#include "task.h"

#include "term_io.h"


#define FILE_BUF_SIZE 1024
static FIL file;
static char fileBuffer[FILE_BUF_SIZE];

static void init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    led_init();

    debug_init_default();

    RCC_ClocksTypeDef RCC_ClocksStatus;
    RCC_GetClocksFreq(&RCC_ClocksStatus);
    xprintf("Clockz info: APB1 = %d Hz, APB2 = %d Hz\n", (int) RCC_ClocksStatus.PCLK1_Frequency, (int) RCC_ClocksStatus.PCLK2_Frequency);

    xprintf("SCB->AIRCR = %x\n", (unsigned int) SCB->AIRCR);
}

int main(void) {
    init();

    led_set(LED_RED, LED_ON);

    uint8_t update = 1;

    uint16_t curr_ver = firmware_curr_version();
    uint16_t new_ver = firmware_new_version();

    led_set(LED_ORANGE, LED_ON);

    if (curr_ver < new_ver) {
        update = 0;
        uint8_t dump_res = firmware_dump();

        uint8_t update_res = firmware_update();
        if (update_res) update = firmware_integrity();

        led_set(LED_BLUE, LED_ON);

        if (!update) {
            led_set(LED_BLUE, LED_OFF);
            if (dump_res) {
                update_res = firmware_restore();
                if (update_res) update = firmware_integrity();
            }
            if (!update) {
                led_set(LED_ORANGE, LED_OFF);
                update_res = firmware_basic();
                if (update_res) update = firmware_integrity();
            }
        }
    }

    if (update) {
        led_set(LED_RED, LED_OFF);
        //de_init();
        firmware_run();
    }
    else {
        for(;;);
    }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    xprintf("FreeRTOS stack overflow @\n  task name: %s\n  task handle address %X\n", pcTaskName, (int) xTask);
    while (1);
}

void assert_failed(uint8_t* file, uint32_t line) {
    xprintf("\n\n *** assert_failed: file %s , line %x\n", (char*) file, (unsigned int) line);
}
