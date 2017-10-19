#ifndef __FIRMWARE_H
#define __FIRMWARE_H

#include "stm32f4xx.h"

uint8_t firmware_init(void);
uint8_t firmware_deinit(void);
uint16_t firmware_curr_version(void);
uint16_t firmware_new_version(void);
uint8_t firmware_dump(void);
uint8_t firmware_update(void);
uint8_t firmware_restore(void);
uint8_t firmware_basic(void);
uint8_t firmware_integrity(void);
void firmware_run(void);

#endif /* __FIRMWARE_H */
