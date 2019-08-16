#include "usart.h"

void NVIC_Config(void)
{
	NVIC_InitTypeDef  NVIC_STRUCT;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_STRUCT.NVIC_IRQChannel = USART1_IRQn;
	NVIC_STRUCT.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_STRUCT.NVIC_IRQChannelSubPriority = 0;
	NVIC_STRUCT.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_STRUCT);
}

void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_STRUCT;
	USART_InitTypeDef USART_STRUCT;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	NVIC_Config();
	
	GPIO_STRUCT.GPIO_Pin = GPIO_Pin_9;
	GPIO_STRUCT.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_STRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_STRUCT);
	
	GPIO_STRUCT.GPIO_Pin = GPIO_Pin_10;
	GPIO_STRUCT.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_STRUCT);
	
	
	USART_STRUCT.USART_BaudRate = 115200;
	USART_STRUCT.USART_WordLength = USART_WordLength_8b;
	USART_STRUCT.USART_StopBits = USART_StopBits_1;
	USART_STRUCT.USART_Parity = USART_Parity_No;
	USART_STRUCT.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_STRUCT.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1,&USART_STRUCT);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	USART_Cmd(USART1,ENABLE);
}


void USART1_Send_Byte(u8 data)
{
	USART_SendData(USART1,data);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
}

void USART1_Send_Str(u8* data)
{
	if(*data)
	{
		USART1_Send_Byte(*data++);
	}
}


int fputc(int ch,FILE* f)
{
	USART_SendData(USART1,ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) ==RESET);
	return ch;
}

