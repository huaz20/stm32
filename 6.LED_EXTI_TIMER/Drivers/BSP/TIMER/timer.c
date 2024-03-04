#include "./BSP/TIMER/timer.h"
#include "STM32F1xx_HAL_Driver\Inc\stm32f1xx_hal_tim.h"


TIM_HandleTypeDef g_timx_handle;

void btim_timx_int_init(uint16_t arr,uint16_t psc)
{
	g_timx_handle.Instance = TIM4;
	g_timx_handle.Init.Prescaler = psc;
	g_timx_handle.Init.Period = arr;
	g_timx_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	g_timx_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	g_timx_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	
	HAL_TIM_Base_Init(&g_timx_handle);
	
	HAL_TIM_Base_Start_IT(&g_timx_handle);
	
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM4)
	{
		__HAL_RCC_TIM4_CLK_ENABLE();//
		HAL_NVIC_SetPriority(TIM4_IRQn,2,2);
		HAL_NVIC_EnableIRQ(TIM4_IRQn);
		
	}
}

void TIM4_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&g_timx_handle);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)/*?*/
{
	if(htim->Instance == TIM4)
	{
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		
	}
}


