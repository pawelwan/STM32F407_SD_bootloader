#include "stm32f4xx.h"
#include "firmware.h"
#include "led.h"
#include "sd.h"

#include "term_io.h"

typedef uint8_t (*func_t)(void);

static void check_and_run(void);
static void update_and_run(func_t update);
static void error(void);
static void init(void);
static void deinit(void);

int main(void) {
    init();

    uint8_t res = firmware_init();
    if (!res) {
        check_and_run();
        error();
    }

    uint16_t curr_ver = firmware_curr_version();
    uint16_t new_ver = firmware_new_version();

    if (curr_ver < new_ver) {
        uint8_t dump_res = firmware_dump();
        led_set(LED_RED, LED_ON);
        update_and_run(firmware_update);
        if (dump_res) {
            led_set(LED_ORANGE, LED_ON);
            update_and_run(firmware_restore);
        }
    }
    else {
        check_and_run();
    }

    led_set(LED_BLUE, LED_ON);
    update_and_run(firmware_basic);
    error();
}

static void check_and_run(void) {
    if (firmware_integrity()) {
        firmware_deinit();
        deinit();
        firmware_run();
    }
}

static void update_and_run(func_t update) {
    if (update()) {
        check_and_run();
    }
}

static void error(void) {
    xprintf("error");
    for(;;);
}

static void init(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    debug_init();
    xprintf("debug initialized");

    led_init();
    xprintf("led initialized");
}

static void deinit(void) {
    SD_LowLevel_DeInit();
    xprintf("SD deinitialized");

    led_deinit();
    xprintf("led deinitialized");

    debug_deinit();
}

void assert_failed(uint8_t* file, uint32_t line) {
    xprintf("\n\n *** assert_failed: file %s , line %x\n", (char*) file, (unsigned int) line);
}
