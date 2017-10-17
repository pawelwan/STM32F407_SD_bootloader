#include "flash.h"

#define FLASH_STEP 0x08
#define INCORRECT_SECTOR 0xFF

static uint8_t clear_sector(uint32_t);
static uint32_t get_sector(uint32_t);

uint8_t flash_clear_sector(uint32_t addr) {
    uint32_t sector = get_sector(addr);
    if (sector == INCORRECT_SECTOR) return 0;
    return clear_sector(sector);
}

uint8_t flash_clear(uint32_t from_addr, uint32_t to_addr) {
    uint8_t res;
    uint32_t first_sector = get_sector(from_addr);
    uint32_t last_sector = get_sector(to_addr);

    if (first_sector == INCORRECT_SECTOR || last_sector == INCORRECT_SECTOR) return 0;

    while (first_sector != last_sector) {
        res = clear_sector(first_sector);
        if (res == 0) return 0;
        first_sector += FLASH_STEP;
    }

    return clear_sector(last_sector);
}

uint32_t flash_program_by_word(uint32_t addr, const uint32_t *data, uint32_t size) {
    FLASH_Status res;
    FLASH_Unlock();

    for (uint32_t i = 0; i < size; ++i) {
        res = FLASH_ProgramWord(addr, data[i]);
        if (res != FLASH_COMPLETE) {
            FLASH_Lock();
            return 0;
        }
        addr += 4;
    }

    FLASH_Lock();
    return addr;
}

uint32_t flash_program_by_byte(uint32_t addr, const uint8_t *data, uint32_t size) {
    FLASH_Status res;
    FLASH_Unlock();

    for (uint32_t i = 0; i < size; ++i) {
        res = FLASH_ProgramByte(addr, data[i]);
        if (res != FLASH_COMPLETE) {
            FLASH_Lock();
            return 0;
        }
        ++addr;
    }

    FLASH_Lock();
    return addr;
}

static uint8_t clear_sector(uint32_t sector) {
    //unlock the FLASH control register access
    FLASH_Unlock();

    //Clear all FLASH pending flags
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
                    FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

    //VoltageRange_3 - operation will be done by word (32-bit)
    FLASH_Status res = FLASH_EraseSector(sector, VoltageRange_3);

    //lock the FLASH control register access
    FLASH_Lock();

    return (res == FLASH_COMPLETE) ? 1 : 0;
}

static uint32_t get_sector(uint32_t addr) {
    if (!IS_FLASH_ADDRESS(addr)) return INCORRECT_SECTOR;

    if((addr >= FLASH_SECTOR_0_ADDR) && (addr < FLASH_SECTOR_1_ADDR))
        return FLASH_Sector_0;
    if((addr >= FLASH_SECTOR_1_ADDR) && (addr < FLASH_SECTOR_2_ADDR))
        return FLASH_Sector_1;
    if((addr >= FLASH_SECTOR_2_ADDR) && (addr < FLASH_SECTOR_3_ADDR))
        return FLASH_Sector_2;
    if((addr >= FLASH_SECTOR_3_ADDR) && (addr < FLASH_SECTOR_4_ADDR))
        return FLASH_Sector_3;
    if((addr >= FLASH_SECTOR_4_ADDR) && (addr < FLASH_SECTOR_5_ADDR))
        return FLASH_Sector_4;
    if((addr >= FLASH_SECTOR_5_ADDR) && (addr < FLASH_SECTOR_6_ADDR))
        return FLASH_Sector_5;
    if((addr >= FLASH_SECTOR_6_ADDR) && (addr < FLASH_SECTOR_7_ADDR))
        return FLASH_Sector_6;
    if((addr >= FLASH_SECTOR_7_ADDR) && (addr < FLASH_SECTOR_8_ADDR))
        return FLASH_Sector_7;
    if((addr >= FLASH_SECTOR_8_ADDR) && (addr < FLASH_SECTOR_9_ADDR))
        return FLASH_Sector_8;
    if((addr >= FLASH_SECTOR_9_ADDR) && (addr < FLASH_SECTOR_10_ADDR))
        return FLASH_Sector_9;
    if((addr >= FLASH_SECTOR_10_ADDR) && (addr < FLASH_SECTOR_11_ADDR))
        return FLASH_Sector_10;

    return FLASH_Sector_11;
}
