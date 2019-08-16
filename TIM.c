#include "TIM.h"


void TIM3_Config(u16 x)
{
	GPIO_InitTypeDef GPIO_STRUCT;
	TIM_TimeBaseInitTypeDef TIM_STRUCT;
	TIM_OCInitTypeDef TIM_OCSTRUCT;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	
	GPIO_STRUCT.GPIO_Pin = GPIO_Pin_6;
	GPIO_STRUCT.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_STRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_STRUCT);
	
	TIM_STRUCT.TIM_Period = 999;
	TIM_STRUCT.TIM_Prescaler = 0;
	TIM_STRUCT.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_STRUCT.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_STRUCT);
	
	

	TIM_OCSTRUCT.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCSTRUCT.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCSTRUCT.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCSTRUCT.TIM_Pulse = x;
	
	TIM_OC1Init(TIM3,&TIM_OCSTRUCT);
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	
	TIM_Cmd(TIM3,ENABLE);
	
}

