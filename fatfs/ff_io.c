#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "diskio.h"
#include "sd.h"

#include "term_io.h"

#define SD_CARD		0

DSTATUS status[2] = {STA_NOINIT,STA_NOINIT};

DWORD get_fattime (void)
{
	return(0);
}

DSTATUS disk_initialize (BYTE lun)
{
	xprintf("disk_initialize, lun=%d\n",lun);

	switch(lun)
	{
		case SD_CARD:
		{
			debug_msg("Initializing SD Card...");

			for(int i=0;i<5;i++)
			{
				xprintf("--- initializing SD card, try %d\n",i+1);
				if(sdInit()==0)
				{
					debug_msg("SD Card init OK");
					status[lun] = 0;
					return(0);
				}
				vTaskDelay(200);
			}
			debug_msg("SD Card init failed");
			status[lun] = STA_NOINIT;
			return(STA_NOINIT);
		}
	}

	return(STA_NOINIT);
}

DSTATUS disk_status (BYTE lun)
{
	xprintf("disk_status rq, lun=%d, returning %d\n",lun,status[lun]);
	return(status[lun]);
}

DRESULT disk_read (BYTE lun, BYTE* buffer, DWORD lba, BYTE count)
{
	//if (status[lun] == STA_NOINIT) return RES_NOTRDY;

	switch(lun)
	{
		case SD_CARD:
		{
			if(
				sdReadBlocks(lba,count,buffer) != 0
				)
				{
					xprintf("sdReadBlocks error, lba=%X, count=%X\n",(unsigned)lba,(unsigned)count);
					return(RES_ERROR);
				}
			return(RES_OK);
		}

	}

	xprintf("disk read, returning RES_NOTRDY\n");
	return RES_NOTRDY;
}

#if	_READONLY == 0
DRESULT disk_write (BYTE lun, const BYTE* buffer, DWORD lba, BYTE count)
{
	//if (status[lun] == STA_NOINIT) return RES_NOTRDY;

	switch(lun)
	{
		case SD_CARD:
		{
			if(
				sdWriteBlocks(lba,count,buffer) != 0
				)
				{
					xprintf("sdReadBlocks error, lba=%X, count=%X\n",(unsigned)lba,(unsigned)count);
					return(RES_ERROR);
				}
			return(RES_OK);
		}
	}
	xprintf("disk write, returning RES_NOTRDY\n");
	return RES_NOTRDY;
}

#endif



DRESULT disk_ioctl (BYTE lun, BYTE ctrl, void * response)
{
	switch(lun)
	{
		case SD_CARD:
		{
			switch(ctrl)
			{
				case CTRL_SYNC:
				{
					return(RES_OK);
				}
				case GET_SECTOR_COUNT:
				{
					uint32_t max_lba;
					uint16_t block_size;
					sdGetSizeInfo(&max_lba,&block_size);
					*(DWORD*)response = max_lba;
					xprintf("fatFS, GET_SECTOR_COUNT, returning value %X\n",(unsigned)max_lba);
					return(RES_OK);
				}
				case GET_BLOCK_SIZE:
				{
					debug_msg("fatFS, GET_SECTOR_SIZE, returning value 1");
					*(DWORD*)response = 1;
					return(RES_OK);
				}
				case GET_SECTOR_SIZE:
				{
					uint32_t max_lba;
					uint16_t block_size;
					sdGetSizeInfo(&max_lba,&block_size);
					*(DWORD*)response = block_size;
					xprintf("fatFS, GET_SECTOR_SIZE, returning value %X\n",(unsigned)block_size);
					return(RES_OK);
				}
				case CTRL_ERASE_SECTOR:
				{
					debug_msg("CTRL_ERASE_SECTOR, returning OK");
					return(RES_OK);
				}
			}
		}
	}
	return(RES_PARERR);
}
