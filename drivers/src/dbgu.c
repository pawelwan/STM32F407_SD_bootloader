#include "dbgu.h"

#define USARTx USART1

void dbg_shdn(uint32_t shdn_on)
{
	if(shdn_on)
	{
		RCC->APB2ENR &=~RCC_APB2Periph_USART1;
	}
	else
	{
		RCC->APB2ENR |= RCC_APB2Periph_USART1;
	}


}


void debug_init_default(void)
{
	// Enable peripheral clocks
	//
	RCC->AHB1ENR |= RCC_AHB1Periph_GPIOB;
	RCC->APB2ENR |= RCC_APB2Periph_USART1;

	// Initialize Serial Port
	//
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

int debug_test(void)
{
	return ( USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET ) ? 0 : 1;
}


//send chr via UART (platform dependent)
void debug_chr(char chr)
{
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET) { ; }
	USART_SendData(USARTx, (uint16_t)chr);
}



//returns ascii value of last char received
//returns 0 if no char was received since last debug_inkey call
//(platform dependent)
char debug_inkey(void)
{
	if(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET)
		return(0);
	else
		return (unsigned char)USART_ReceiveData(USARTx);
}

//halts program/task execution until char is received
//(platform dependent)
char debug_waitkey(void)
{
	while(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET) { ; }
	return (unsigned char)USART_ReceiveData(USARTx);
}


//platform independent funcs


//prints text starting at str
//adds new line at end
void debug_msg(const char *str)
{
	debug_txt(str);
	debug_chr('\r');
	debug_chr('\n');
}

//prints text starting at str
void debug_txt(const char *str)
{
	while(*str) debug_chr(*str++);
}
