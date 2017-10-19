#include "stm32f4xx.h"
#include "firmware.h"
#include "led.h"

#include "term_io.h"

typedef uint8_t (*func_t)(void);

static void error(void);
static void check_and_run(void);
static uint8_t update_and_check(func_t func);
static void deinit_and_run(void);
static void init(void);
static void deinit(void);

int main(void) {
    init();

    uint8_t res = firmware_init();
    if (!res) check_and_run();

    uint16_t curr_ver = firmware_curr_version();
    uint16_t new_ver = firmware_new_version();

    if (curr_ver >= new_ver) check_and_run();
    else {
        uint8_t update;
        uint8_t dump_res = firmware_dump();

        update = update_and_check(firmware_update);
        if (update) deinit_and_run();

        if (dump_res) {
            update = update_and_check(firmware_restore);
            if (update) deinit_and_run();
        }

        update = update_and_check(firmware_basic);
        if (update) deinit_and_run();
    }

    error();
}

static void error(void) {
    xprintf("error");
    for(;;);
}

static void check_and_run(void) {
    if (firmware_integrity()) deinit_and_run();
    else error();
}

static uint8_t update_and_check(func_t func) {
    uint8_t update_res = func();
    if (update_res) return firmware_integrity();
    return 0;
}

static void deinit_and_run(void) {
    firmware_deinit();
    deinit();
    firmware_run();
}

static void init(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    debug_init();
    xprintf("debug initialized");

    led_init();
    xprintf("led initialized");
}

static void deinit(void) {
    led_deinit();
    xprintf("led deinitialized");

    debug_deinit();
}

void assert_failed(uint8_t* file, uint32_t line) {
    xprintf("\n\n *** assert_failed: file %s , line %x\n", (char*) file, (unsigned int) line);
}
