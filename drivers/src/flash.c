#include "flash.h"

#include "term_io.h"

static uint32_t flash_get_sector(uint32_t);

uint8_t flash_clear_sector(uint32_t addr) {
    //unlock the FLASH control register access
    FLASH_Unlock();

    //Clear all FLASH pending flags
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
                    FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

    uint32_t sector = flash_get_sector(addr);

    //VoltageRange_3 - operation will be done by word (32-bit)
    FLASH_Status res = FLASH_EraseSector(sector, VoltageRange_3);

    //lock the FLASH control register access
    FLASH_Lock();

    return (res == FLASH_COMPLETE) ? 1 : 0;
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
        addr += 4;
    }

    FLASH_Lock();
    return addr;
}

static uint32_t flash_get_sector(uint32_t addr) {
    uint32_t sector = 0;

    if((addr >= FLASH_SECTOR_0_ADDR) && (addr < FLASH_SECTOR_1_ADDR))
        sector = FLASH_Sector_0;
    else if((addr >= FLASH_SECTOR_1_ADDR) && (addr < FLASH_SECTOR_2_ADDR))
        sector = FLASH_Sector_1;
    else if((addr >= FLASH_SECTOR_2_ADDR) && (addr < FLASH_SECTOR_3_ADDR))
        sector = FLASH_Sector_2;
    else if((addr >= FLASH_SECTOR_3_ADDR) && (addr < FLASH_SECTOR_4_ADDR))
        sector = FLASH_Sector_3;
    else if((addr >= FLASH_SECTOR_4_ADDR) && (addr < FLASH_SECTOR_5_ADDR))
        sector = FLASH_Sector_4;
    else if((addr >= FLASH_SECTOR_5_ADDR) && (addr < FLASH_SECTOR_6_ADDR))
        sector = FLASH_Sector_5;
    else if((addr >= FLASH_SECTOR_6_ADDR) && (addr < FLASH_SECTOR_7_ADDR))
        sector = FLASH_Sector_6;
    else if((addr >= FLASH_SECTOR_7_ADDR) && (addr < FLASH_SECTOR_8_ADDR))
        sector = FLASH_Sector_7;
    else if((addr >= FLASH_SECTOR_8_ADDR) && (addr < FLASH_SECTOR_9_ADDR))
        sector = FLASH_Sector_8;
    else if((addr >= FLASH_SECTOR_9_ADDR) && (addr < FLASH_SECTOR_10_ADDR))
        sector = FLASH_Sector_9;
    else if((addr >= FLASH_SECTOR_10_ADDR) && (addr < FLASH_SECTOR_11_ADDR))
        sector = FLASH_Sector_10;
    else
        sector = FLASH_Sector_11;

    return sector;
}
