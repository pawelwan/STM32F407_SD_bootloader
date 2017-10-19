#include <string.h>

#include "stm32f4xx.h"
#include "firmware.h"
#include "led.h"
#include "sd.h"
#include "ff.h"

#include "term_io.h"

static void init(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    led_init();
    debug_init();

    RCC_ClocksTypeDef RCC_ClocksStatus;
    RCC_GetClocksFreq(&RCC_ClocksStatus);

    xprintf("Clockz info: APB1 = %d Hz, APB2 = %d Hz\n", (int) RCC_ClocksStatus.PCLK1_Frequency, (int) RCC_ClocksStatus.PCLK2_Frequency);
    xprintf("SCB->AIRCR = %x\n", (unsigned int) SCB->AIRCR);
}

static void deinit(void) {
    led_deinit();
    debug_deinit();
}

int main(void) {
    init();

    led_set(LED_RED, LED_ON);

    uint8_t update = 1;

    firmware_init();  // TODO: check if mounted

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

    deinit();

    if (update) {
        led_set(LED_RED, LED_OFF);
        //de_init();
        firmware_run();
    }
    else {
        for(;;);
    }
}

void assert_failed(uint8_t* file, uint32_t line) {
    xprintf("\n\n *** assert_failed: file %s , line %x\n", (char*) file, (unsigned int) line);
}
