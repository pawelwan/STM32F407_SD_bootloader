#ifndef __FIRMWARE_CONF_H
#define __FIRMWARE_CONF_H

typedef struct {
    uint8_t entry_sign;
    uint32_t crc;
    uint32_t crc_shadow;
    uint32_t size;          //  Size of firmware image
    uint32_t uuid;          //  Integer representing unique firmware ID
    uint16_t version;       //  Integer representing firmware version
    uint8_t closing_sign;
} FirmwareHeader_t;

#define ENTRY_VALUE 0x7E
#define CLOSE_VALUE 0xFE

#define ENTRY_OFFSET 0
#define CRC_OFFSET (ENTRY_OFFSET + sizeof(uint8_t))
#define CRC_SHADOW_OFFSET (CRC_OFFSET + sizeof(uint32_t))
#define SIZE_OFFSET (CRC_SHADOW_OFFSET + sizeof(uint32_t))
#define UUID_OFFSET (SIZE_OFFSET + sizeof(uint32_t))
#define VERSION_OFFSET (UUID_OFFSET + sizeof(uint32_t))
#define CLOSE_OFFSET (VERSION_OFFSET + sizeof(uint16_t))
#define HEADER_SIZE (CLOSE_OFFSET + sizeof(uint8_t))

#define DRIVE_NO 0
#define NEW_NAME "new.bin"
#define CURR_NAME "current.bin"
#define BASIC_NAME "basic.bin"

#endif /* __FIRMWARE_CONF_H */
