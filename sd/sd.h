#ifndef __SD_H__
#define __SD_H__

#include "stm32f4xx.h"

void SD_LowLevel_DeInit(void);
void SD_LowLevel_Init(void);
void SD_LowLevel_DMA_TxConfig(uint32_t *BufferSRC, uint32_t BufferSize);
void SD_LowLevel_DMA_RxConfig(uint32_t *BufferDST, uint32_t BufferSize);

int sdInit(void);
int sdGetSizeInfo(uint32_t *NumberOfBlocks, uint16_t *BlockSize);
int sdReadBlock(uint32_t BlockAddress, uint8_t *Buffer);
int sdWriteBlock(uint32_t BlockAddress, uint8_t *Buffer);
int sdReadBlocks(uint32_t BlockAddress, uint8_t blocks, uint8_t *Buffer);
int sdWriteBlocks(uint32_t BlockAddress, uint8_t blocks, uint8_t *Buffer);


#endif
