#include "./BSP/TIMER/gtim.h"
#include "./SYSTEM/sys/sys.h"

TIM_HandleTypeDef g_timx_cap_chy_handle;  /*句柄*/

void gtim_timx_cap_chy_init(uint16_t arr, uint16_t psc)
{
			
		g_timx_cap_chy_handle.Instance = TIM2;
		g_timx_cap_chy_handle.Init.Prescaler = psc;
		g_timx_cap_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP ;
		g_timx_cap_chy_handle.Init.Period = arr;

		HAL_TIM_IC_Init(&g_timx_cap_chy_handle);
		 
		TIM_IC_InitTypeDef timx_ic_cap_chy = {0};
	
		timx_ic_cap_chy.ICPolarity = TIM_ICPOLARITY_RISING;  /*上升沿捕获*/
		timx_ic_cap_chy.ICFilter = 0 ;  /*输入滤波器 bulvbo*/
		timx_ic_cap_chy.ICPrescaler = TIM_ICPSC_DIV1;  /*配置输入分频  DIV1 不分频*/
		timx_ic_cap_chy.ICSelection = TIM_ICSELECTION_DIRECTTI;/*映射到TTI上*/
		
		HAL_TIM_IC_ConfigChannel(&g_timx_cap_chy_handle,&timx_ic_cap_chy,TIM_CHANNEL_3);
		
		__HAL_TIM_ENABLE_IT(&g_timx_cap_chy_handle,TIM_IT_UPDATE);  /*使能更新中断*/
		HAL_TIM_IC_Start_IT(&g_timx_cap_chy_handle,TIM_CHANNEL_3); /*开始捕获*/


	
}


void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2)
	{
			GPIO_InitTypeDef gpio_init_struct={0};
			
			__HAL_RCC_GPIOB_CLK_ENABLE();
			__HAL_RCC_TIM2_CLK_ENABLE();
			
			gpio_init_struct.Pin = GPIO_PIN_10;
			gpio_init_struct.Mode = GPIO_MODE_AF_PP;
			gpio_init_struct.Pull = GPIO_PULLDOWN;
			gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH ;
			
			HAL_GPIO_Init(GPIOB,&gpio_init_struct);
			
			HAL_NVIC_SetPriority(TIM2_IRQn,1,3);
			HAL_NVIC_EnableIRQ(TIM2_IRQn);
		
	
	
}
	}
	
uint8_t g_timxchy_cap_sta = 0;/*输入捕获状态*/
uint16_t g_timxchy_cap_val = 0;/*输入捕获之*/

void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_timx_cap_chy_handle);
}


/* 定时器输入捕获中断处理回调函数 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        if ((g_timxchy_cap_sta & 0X80) == 0)    /* 还没有成功捕获 */
        {
            if (g_timxchy_cap_sta & 0X40) /* 捕获下降沿 */
            {
                g_timxchy_cap_sta |= 0X80; /* 捕获到一次高电平 */
                g_timxchy_cap_val = HAL_TIM_ReadCapturedValue(&g_timx_cap_chy_handle, TIM_CHANNEL_3);
                TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, TIM_CHANNEL_3);  /* 清除原来设置*/
                TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, TIM_CHANNEL_3, TIM_ICPOLARITY_RISING);
            }
            else /* 还未开始,第一次捕获上升沿 */
            {
                g_timxchy_cap_sta = 0;
                g_timxchy_cap_val = 0;
                g_timxchy_cap_sta |= 0X40;    /* 捕获到上升沿 */
                __HAL_TIM_DISABLE(&g_timx_cap_chy_handle);
                __HAL_TIM_SET_COUNTER(&g_timx_cap_chy_handle, 0);
                TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, TIM_CHANNEL_3); /*清除原来设置*/
                TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, TIM_CHANNEL_3, TIM_ICPOLARITY_FALLING);
                __HAL_TIM_ENABLE(&g_timx_cap_chy_handle);
            }
        }
    }
}

/* 定时器更新中断回调函数 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        if ((g_timxchy_cap_sta & 0X80) == 0)/* 还未成功捕获 */
        {
            if (g_timxchy_cap_sta & 0X40) /* 捕获高电平*/
            {
                if ((g_timxchy_cap_sta & 0X3F) == 0X3F)
                {
                    TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, TIM_CHANNEL_3);
                    TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, TIM_CHANNEL_3, TIM_ICPOLARITY_RISING);
                    g_timxchy_cap_sta |= 0X80;
                    g_timxchy_cap_val = 0XFFFF;
                }
                else
                {
                    g_timxchy_cap_sta++;/*溢出次数*/
                }
            }
        }
    }
}

