#include <string.h>

#include "stm32f4xx.h"
#include "firmware.h"
#include "led.h"
#include "sd.h"
#include "ff.h"
#include "FreeRTOS.h"
#include "task.h"
#include "usbh_usr.h"

#include "term_io.h"


#define FILE_BUF_SIZE 1024
static FIL file;
static char fileBuffer[FILE_BUF_SIZE];

USB_OTG_CORE_HANDLE USB_OTG_Core;
USBH_HOST USB_Host;
USBH_Usr_Result_t USBH_Usr_INT_Result;

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

static void testproc(void) {
    uint8_t key = debug_inkey();
    char* sampleText = "sample text";

    int res = 0;

    switch (key) {
        case 'i':
            xprintf("sdinit...\n");
            res = sdInit();
            xprintf("sdInit res=%d\n", res);
            break;
        case 's':
        {
            uint32_t nob;
            uint16_t bsize;
            xprintf("reading card info...\n");
            res = sdGetSizeInfo(&nob, &bsize);
            xprintf("card info res=%d, nob=%d, bsize=%x\n", res, (unsigned int) nob, (unsigned int) bsize);
            break;
        }
        case 'w':
        {
            f_chdrive(1);
            xprintf("File writing test. File open...\n");
            FRESULT res = f_open(&file, "test.txt", FA_WRITE | FA_CREATE_ALWAYS);
            if (res == FR_OK) xprintf("OK");
            else {
                xprintf("error: 0x%x\n", res);
                break;
            }
            UINT written;
            strcpy(fileBuffer, "It's a test!");
            res = f_write(&file, sampleText, strlen(sampleText), &written);
            xprintf("write finished with result 0x%X, %d bytes written\n", res, written);
            f_close(&file);
            break;
        }
        case 'r':
        {
            f_chdrive(1);
            xprintf("File reading test. File open...\n");
            FRESULT res = f_open(&file, "test.txt", FA_READ);
            if (res == FR_OK) xprintf("OK");
            else {
                xprintf("error: 0x%x\n", res);
                break;
            }
            UINT read;
            res = f_read(&file, fileBuffer, FILE_BUF_SIZE, &read);
            xprintf("read finished with result 0x%X, %d bytes read, contents:\n", res, read);
            debug_txt(fileBuffer);
            f_close(&file);
            break;
        }
    }
}

static void taskUsb(void* params) {
    portENTER_CRITICAL();
    USBH_Init(&USB_OTG_Core,
            USB_OTG_FS_CORE_ID,
            &USB_Host,
            &USBH_MSC_cb,
            &USR_Callbacks);
    xprintf("USB Host driver initialized\n");

    portEXIT_CRITICAL();


    while (1) {

        USBH_Process(&USB_OTG_Core, &USB_Host);

        testproc();

        vTaskDelay(5);
    }
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

    int res1 = xTaskCreate(taskUsb, "usb", configMINIMAL_STACK_SIZE + 100, NULL, 3, NULL);
    xprintf("taskUsb xTaskCreate returned %d\n", res1);

    vTaskStartScheduler();
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    xprintf("FreeRTOS stack overflow @\n  task name: %s\n  task handle address %X\n", pcTaskName, (int) xTask);
    while (1);
}

void assert_failed(uint8_t* file, uint32_t line) {
    xprintf("\n\n *** assert_failed: file %s , line %x\n", (char*) file, (unsigned int) line);
}
