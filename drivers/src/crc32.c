#include "crc32.h"

void crc32_init(uint32_t *crc) {
    *crc = 0xFFFFFFFF;
}

void crc32_next(uint32_t *crc, const uint8_t *data, uint32_t size) {
    uint32_t byte, mask;
    uint32_t crc_c = *crc;

    for(uint32_t i = 0; i < size; ++i) {
        byte = data[i];
        crc_c = crc_c ^ byte;
        for (uint8_t j = 0; j < 8; ++j) {
            mask = -(crc_c & 1);
            crc_c = (crc_c >> 1) ^ (0xEDB88320 & mask);
        }
    }

    *crc = crc_c;
}

void crc32_res(uint32_t *crc) {
    *crc = ~(*crc);
}
