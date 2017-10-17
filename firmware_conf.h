#ifndef __FIRMWARE_CONF_H
#define __FIRMWARE_CONF_H

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

#endif /* __FIRMWARE_CONF_H */
