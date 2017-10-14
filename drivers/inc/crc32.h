#ifndef __CRC32_H
#define __CRC32_H

#include "stm32f4xx.h"

// initialize crc
void crc32_init(uint32_t *crc);

// update crc (must be initialized)
void crc32_next(uint32_t *crc, const uint8_t *data, uint32_t size);

// get final result of crc
void crc32_res(uint32_t *crc);

#endif /* __CRC32_H */
