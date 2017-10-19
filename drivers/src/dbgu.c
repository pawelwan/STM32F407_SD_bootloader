#include "dbgu.h"


void debug_init(void) {
	// Enable peripheral clocks
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	// Initialize Serial Port
	GPIO_Init(GPIOB, &(GPIO_InitTypeDef) {
		.GPIO_Pin   = GPIO_Pin_6,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode  = GPIO_Mode_AF,
		.GPIO_OType = GPIO_OType_PP
	});

	GPIO_Init(GPIOB, &(GPIO_InitTypeDef) {
		.GPIO_Pin = GPIO_Pin_7,
		.GPIO_Mode = GPIO_Mode_AF,
		.GPIO_PuPd = GPIO_PuPd_UP
	});

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

	USART_Init(USART1, &(USART_InitTypeDef) {
		.USART_BaudRate = 115200,
		.USART_WordLength = USART_WordLength_8b,
		.USART_StopBits = USART_StopBits_1,
		.USART_Parity = USART_Parity_No ,
		.USART_HardwareFlowControl = USART_HardwareFlowControl_None,
		.USART_Mode = USART_Mode_Rx | USART_Mode_Tx
	});

	USART_Cmd(USART1, ENABLE);
}

void debug_deinit(void) {
	USART_Cmd(USART1, DISABLE);
	USART_DeInit(USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_MCO);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_MCO);
	GPIO_DeInit(GPIOB);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, DISABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE);
}

int debug_test(void) {
	return (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET) ? 0 : 1;
}

// send chr via UART (platform dependent)
void debug_chr(char chr) {
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1, (uint16_t) chr);
}

// halts program/task execution until char is received
char debug_waitkey(void) {
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	return (unsigned char) USART_ReceiveData(USART1);
}
