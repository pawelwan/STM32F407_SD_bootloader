#ifndef __FIRMWARE_H
#define __FIRMWARE_H

#include "stm32f4xx.h"

typedef struct {
    uint8_t entry_sign;
    uint32_t crc;
    uint32_t crc_shadow;
    uint32_t size;
    uint32_t uuid;
    uint16_t version;
    uint8_t closing_sign;
} FirmwareHeader_t;

#define HEADER_SIZE sizeof(FirmwareHeader_t)

#define DRIVE_NO 0
//#define ROOT_DIR "/"
#define NEW_NAME "new.bin"
#define CURR_NAME "current.bin"
#define BASIC_NAME "basic.bin"

uint16_t firmware_curr_version(void);
uint16_t firmware_new_version(void);
uint8_t firmware_dump(void);
uint8_t firmware_update(void);
uint8_t firmware_restore(void);
uint8_t firmware_basic(void);
uint8_t firmware_integrity(void);
void firmware_run(void);

#endif /* __FIRMWARE_H */
