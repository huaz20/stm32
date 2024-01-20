#include "./BSP/EXTI/exti.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"

void exti_init(void)
{
		GPIO_InitTypeDef gpio_init_struct={0};
		
		__HAL_RCC_GPIOA_CLK_ENABLE();
		
		gpio_init_struct.Pin = GPIO_PIN_4;
		gpio_init_struct.Mode = GPIO_MODE_IT_RISING_FALLING;
		gpio_init_struct.Pull = GPIO_NOPULL;
		
		HAL_GPIO_Init(GPIOA,&gpio_init_struct);
		 
		HAL_NVIC_SetPriority(EXTI4_IRQn,2,0);
		HAL_NVIC_EnableIRQ(EXTI4_IRQn);
}

void EXTI4_IRQHandler(void)
{
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
			delay_ms(20);
			if(GPIO_Pin==GPIO_PIN_4)
			{
					if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==1)
					{
						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
					
					}

					if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==0)
					{
						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
					
					}
			}
}
