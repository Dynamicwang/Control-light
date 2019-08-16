#include "adc.h"

uint16_t Conver_Value[10];

void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_STRUCT;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_STRUCT.GPIO_Pin = GPIO_Pin_0;
	GPIO_STRUCT.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC,&GPIO_STRUCT);
}

void DMA_Config(void)
{
	DMA_InitTypeDef DMA_STRUCT;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_STRUCT.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);
	DMA_STRUCT.DMA_MemoryBaseAddr = (uint32_t) &Conver_Value;
	DMA_STRUCT.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_STRUCT.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_STRUCT.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_STRUCT.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_STRUCT.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_STRUCT.DMA_BufferSize = 10;
	DMA_STRUCT.DMA_Priority = DMA_Priority_Medium;
	DMA_STRUCT.DMA_M2M = DMA_M2M_Disable;
	DMA_STRUCT.DMA_Mode = DMA_Mode_Circular;
	DMA_Init(DMA1_Channel1,&DMA_STRUCT);
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
}

void ADC1_Config(void)
{
	ADC_InitTypeDef ADC_STRUCT;
	
	GPIO_Config();
	DMA_Config();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	ADC_STRUCT.ADC_Mode = ADC_Mode_Independent;
	ADC_STRUCT.ADC_ContinuousConvMode = ENABLE;
	ADC_STRUCT.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_STRUCT.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_STRUCT.ADC_ScanConvMode = ENABLE;
	ADC_STRUCT.ADC_NbrOfChannel = 1;
	
	ADC_Init(ADC1,&ADC_STRUCT);
	
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_10,1,ADC_SampleTime_55Cycles5);
	
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
}

