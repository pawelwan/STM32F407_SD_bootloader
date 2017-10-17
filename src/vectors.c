#include "stm32f4xx.h"
#include "stm32f4_sdio_sd.h"
#include "term_io.h"


void default_handler_c (unsigned int * hardfault_args)
{
  unsigned int stacked_r0;
  unsigned int stacked_r1;
  unsigned int stacked_r2;
  unsigned int stacked_r3;
  unsigned int stacked_r12;
  unsigned int stacked_lr;
  unsigned int stacked_pc;
  unsigned int stacked_psr;

  stacked_r0 = ((unsigned long) hardfault_args[0]);
  stacked_r1 = ((unsigned long) hardfault_args[1]);
  stacked_r2 = ((unsigned long) hardfault_args[2]);
  stacked_r3 = ((unsigned long) hardfault_args[3]);

  stacked_r12 = ((unsigned long) hardfault_args[4]);
  stacked_lr = ((unsigned long) hardfault_args[5]);
  stacked_pc = ((unsigned long) hardfault_args[6]);
  stacked_psr = ((unsigned long) hardfault_args[7]);

  xprintf ("\n\n[Default Handler]\n");
  xprintf ("R0 = %x\n", stacked_r0);
  xprintf ("R1 = %x\n", stacked_r1);
  xprintf ("R2 = %x\n", stacked_r2);
  xprintf ("R3 = %x\n", stacked_r3);
  xprintf ("R12 = %x\n", stacked_r12);
  xprintf ("LR [R14] = %x  subroutine call return address\n", stacked_lr);
  xprintf ("PC [R15] = %x  program counter\n", stacked_pc);
  xprintf ("PSR = %x\n", stacked_psr);
  xprintf ("BFAR = %x\n", (*((volatile unsigned *)(0xE000ED38))));
  xprintf ("CFSR = %x\n", (*((volatile unsigned *)(0xE000ED28))));
  xprintf ("HFSR = %x\n", (*((volatile unsigned *)(0xE000ED2C))));
  xprintf ("DFSR = %x\n", (*((volatile unsigned *)(0xE000ED30))));
  xprintf ("AFSR = %x\n", (*((volatile unsigned *)(0xE000ED3C))));
  xprintf ("SCB_SHCSR = %x\n", (unsigned)SCB->SHCSR);

  while (1);
}



/**
  * @brief  This function handles External line 10 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{
}


/**
  * @brief  This function handles ethernet DMA interrupt request.
  * @param  None
  * @retval None
  */
void ETH_IRQHandler(void)
{
}


void SDIO_IRQHandler(void)
{
	//xprintf("SDIO IRQ!\n");
	SD_ProcessIRQSrc();
}

void SD_SDIO_DMA_IRQHANDLER(void)
{
	//xprintf("SDIO DMA IRQ!\n");
	SD_ProcessDMAIRQ();
}



/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
	xprintf("NMI_Handler");
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
/*void HardFault_Handler(void)
{
  //Go to infinite loop when Hard Fault exception occurs*/
  /*while (1)
  {
  }
}*/


void hard_fault_handler_c (unsigned int * hardfault_args)
{
  unsigned int stacked_r0;
  unsigned int stacked_r1;
  unsigned int stacked_r2;
  unsigned int stacked_r3;
  unsigned int stacked_r12;
  unsigned int stacked_lr;
  unsigned int stacked_pc;
  unsigned int stacked_psr;

  stacked_r0 = ((unsigned long) hardfault_args[0]);
  stacked_r1 = ((unsigned long) hardfault_args[1]);
  stacked_r2 = ((unsigned long) hardfault_args[2]);
  stacked_r3 = ((unsigned long) hardfault_args[3]);

  stacked_r12 = ((unsigned long) hardfault_args[4]);
  stacked_lr = ((unsigned long) hardfault_args[5]);
  stacked_pc = ((unsigned long) hardfault_args[6]);
  stacked_psr = ((unsigned long) hardfault_args[7]);

  xprintf ("\n\n[Hard fault handler - all numbers in hex]\n");
  xprintf ("R0 = %x\n", stacked_r0);
  xprintf ("R1 = %x\n", stacked_r1);
  xprintf ("R2 = %x\n", stacked_r2);
  xprintf ("R3 = %x\n", stacked_r3);
  xprintf ("R12 = %x\n", stacked_r12);
  xprintf ("LR [R14] = %x  subroutine call return address\n", stacked_lr);
  xprintf ("PC [R15] = %x  program counter\n", stacked_pc);
  xprintf ("PSR = %x\n", stacked_psr);
  xprintf ("BFAR = %x\n", (*((volatile unsigned *)(0xE000ED38))));
  xprintf ("CFSR = %x\n", (*((volatile unsigned *)(0xE000ED28))));
  xprintf ("HFSR = %x\n", (*((volatile unsigned *)(0xE000ED2C))));
  xprintf ("DFSR = %x\n", (*((volatile unsigned *)(0xE000ED30))));
  xprintf ("AFSR = %x\n", (*((volatile unsigned *)(0xE000ED3C))));
  xprintf ("SCB_SHCSR = %x\n", (unsigned)SCB->SHCSR);

  while (1);
}


/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
	xprintf("MemManage_Handler");
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
	xprintf("BusFault_Handler");
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
	xprintf("UsageFault_Handler");
  while (1)
  {
  }
}


/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}
