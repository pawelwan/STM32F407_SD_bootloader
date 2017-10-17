#include <stddef.h>

#include "crc32.h"
#include "flash.h"
#include "ff.h"
#include "firmware.h"

#define HEADER_ADDR          FLASH_SECTOR_8_ADDR
#define APP_ADDR             (HEADER_ADDR + HEADER_SIZE)

typedef void (*pFunction)(void);
static uint8_t upload_file(const char* name);

uint16_t firmware_curr_version(void) {
    FirmwareHeader_t *header = (FirmwareHeader_t *) HEADER_ADDR;
    return header->version;
}

uint16_t firmware_new_version(void) {
    FRESULT res;
    FATFS fs;
    FIL file;
    UINT bytes_read;
    FirmwareHeader_t header;

    res = f_mount(DRIVE_NO, &fs);
    if (res) return 0;

    res = f_open(&file, NEW_NAME, FA_OPEN_EXISTING | FA_READ);
    if (res) return 0;

    res = f_read(&file, (void*) &header, HEADER_SIZE, &bytes_read);
    if (res || bytes_read < HEADER_SIZE) return 0;

    res = f_close(&file);
    if (res) return 0;

    res = f_mount(DRIVE_NO, NULL);
    if (res) return 0;

    return header.version;
}

uint8_t firmware_dump(void) {
    FRESULT res;
    FATFS fs;
    FIL file;
    UINT bytes_written;
    FirmwareHeader_t *header = (FirmwareHeader_t *) HEADER_ADDR;
    uint32_t file_size = HEADER_SIZE + header->size;

    res = f_mount(DRIVE_NO, &fs);
    if (res) return 0;

    res = f_open(&file, CURR_NAME, FA_OPEN_ALWAYS | FA_WRITE);
    if (res) return 0;

    res = f_write(&file, (uint8_t *) HEADER_ADDR, file_size, &bytes_written);
    if (res || bytes_written < file_size) return 0;

    res = f_close(&file);
    if (res) return 0;

    res = f_mount(DRIVE_NO, NULL);
    if (res) return 0;

    return 1;
}

uint8_t firmware_update(void) {
    return upload_file(NEW_NAME);
}

uint8_t firmware_restore(void) {
    return upload_file(CURR_NAME);
}

uint8_t firmware_basic(void) {
    return upload_file(BASIC_NAME);
}

uint8_t firmware_integrity(void) {
    uint32_t crc;
    FirmwareHeader_t *header = (FirmwareHeader_t *) HEADER_ADDR;
    uint8_t *addr = (uint8_t *) APP_ADDR;

    crc32_init(&crc);
    crc32_next(&crc, addr, header->size);
    crc32_res(&crc);

    return (crc == header->crc) ? 1 : 0;
}

void firmware_run(void) {
    uint32_t appStack = (uint32_t) *((uint32_t *) APP_ADDR);

    pFunction appEntry = (pFunction) *(uint32_t *) (APP_ADDR + 4);

    SCB->VTOR = APP_ADDR;

    __set_MSP(appStack);

    appEntry();
}

static uint8_t upload_file(const char* name) {
    FRESULT res;
    FATFS fs;
    FIL file;
    UINT bytes_read;
    uint8_t flash_res;
    uint8_t buffer[1024];
    uint32_t addr = HEADER_ADDR;

    res = f_mount(DRIVE_NO, &fs);
    if (res) return 0;

    res = f_open(&file, name, FA_OPEN_EXISTING | FA_READ);
    if (res) return 0;

    flash_res = flash_clear(HEADER_ADDR, FLASH_LAST_ADDR);
    if (flash_res == 0) return 0;

    addr = HEADER_ADDR;
    for (;;) {
        res = f_read(&file, buffer, sizeof(buffer), &bytes_read);
        if (res) return 0;
        if (bytes_read < sizeof(buffer)) break;
        addr = flash_program_by_word(addr, (uint32_t *) buffer, bytes_read / 4);
        if (addr == 0) return 0;
    }

    if (bytes_read > 0) {
        addr = flash_program_by_byte(addr, buffer, bytes_read);
        if (addr == 0) return 0;
    }

    res = f_close(&file);
    if (res) return 0;

    res = f_mount(DRIVE_NO, NULL);
    if (res) return 0;

    return 1;
}
