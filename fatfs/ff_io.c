#include "stm32f4xx.h"
#include "diskio.h"
#include "sd.h"

#include "term_io.h"

#define SD_CARD		0

DSTATUS status = STA_NOINIT;

DWORD get_fattime(void) {
	return 0;
}

DSTATUS disk_initialize(BYTE lun) {
	if (lun == SD_CARD) {
		for (int i = 0; i < 5; i++) {
			if (sdInit() == 0) {
				xprintf("SD Card init OK\r\n");
				status = 0;
				return 0;
			}
		}
	}

	xprintf("SD Card init failed\r\n");
	status = STA_NOINIT;
	return STA_NOINIT;
}

DSTATUS disk_status(BYTE lun) {
	if (lun == SD_CARD) {
		return status;
	}

	return STA_NOINIT;
}

DRESULT disk_read(BYTE lun, BYTE *buffer, DWORD lba, BYTE count) {
	if (lun == SD_CARD) {
		if (sdReadBlocks(lba, count, buffer) != 0) {
			return RES_ERROR;
		}
		return RES_OK;
	}

	return RES_NOTRDY;
}

#if	_READONLY == 0
DRESULT disk_write(BYTE lun, const BYTE *buffer, DWORD lba, BYTE count) {
	if (lun == SD_CARD) {
		if (sdWriteBlocks(lba, count, (uint8_t *) buffer) != 0) {
			return RES_ERROR;
		}
		return RES_OK;
	}

	return RES_NOTRDY;
}
#endif


DRESULT disk_ioctl(BYTE lun, BYTE ctrl, void *response) {
	if (lun == SD_CARD) {
		switch(ctrl) {
			case CTRL_SYNC:
				return RES_OK;
			case GET_SECTOR_COUNT: {
				uint32_t max_lba;
				uint16_t block_size;
				sdGetSizeInfo(&max_lba, &block_size);
				*(DWORD*)response = max_lba;
				return RES_OK;
			}
			case GET_BLOCK_SIZE: {
				*(DWORD*)response = 1;
				return RES_OK;
			}
			case GET_SECTOR_SIZE: {
				uint32_t max_lba;
				uint16_t block_size;
				sdGetSizeInfo(&max_lba, &block_size);
				*(DWORD*)response = block_size;
				return RES_OK;
			}
			case CTRL_ERASE_SECTOR:
				return RES_OK;
		}
	}

	return RES_PARERR;
}
