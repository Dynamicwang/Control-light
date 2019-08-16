#include "usart.h"
#include "TIM.h"
#include "adc.h"

u8 Input_Value = 0;
extern uint16_t Conver_Value[10];
int i;
float temp;

void Init(void)
{
		USART1_Config();
		TIM3_Config(1000);
		ADC1_Config();
}

int main(void)
{
	Init();
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	while(1)
	{
		temp = 0;
		for(i = 0;i < 10;i++)
		{
			temp += Conver_Value[i];
		}
		temp = temp * 3.3 /40960 *1000;
		TIM3_Config((int)(temp/3300 * 1000));
	}
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		USART_ClearFlag(USART1,USART_FLAG_RXNE);
		Input_Value = USART_ReceiveData(USART1);
	}
}
