#include "./BSP/TIMER/gtim.h"
#include "./SYSTEM/sys/sys.h"

TIM_HandleTypeDef g_timx_cap_chy_handle;  /*���*/

void gtim_timx_cap_chy_init(uint16_t arr, uint16_t psc)
{
			
		g_timx_cap_chy_handle.Instance = TIM2;
		g_timx_cap_chy_handle.Init.Prescaler = psc;
		g_timx_cap_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP ;
		g_timx_cap_chy_handle.Init.Period = arr;

		HAL_TIM_IC_Init(&g_timx_cap_chy_handle);
		 
		TIM_IC_InitTypeDef timx_ic_cap_chy = {0};
	
		timx_ic_cap_chy.ICPolarity = TIM_ICPOLARITY_RISING;  /*�����ز���*/
		timx_ic_cap_chy.ICFilter = 0 ;  /*�����˲��� bulvbo*/
		timx_ic_cap_chy.ICPrescaler = TIM_ICPSC_DIV1;  /*���������Ƶ  DIV1 ����Ƶ*/
		timx_ic_cap_chy.ICSelection = TIM_ICSELECTION_DIRECTTI;/*ӳ�䵽TTI��*/
		
		HAL_TIM_IC_ConfigChannel(&g_timx_cap_chy_handle,&timx_ic_cap_chy,TIM_CHANNEL_3);
		
		__HAL_TIM_ENABLE_IT(&g_timx_cap_chy_handle,TIM_IT_UPDATE);  /*ʹ�ܸ����ж�*/
		HAL_TIM_IC_Start_IT(&g_timx_cap_chy_handle,TIM_CHANNEL_3); /*��ʼ����*/


	
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
	
uint8_t g_timxchy_cap_sta = 0;/*���벶��״̬*/
uint16_t g_timxchy_cap_val = 0;/*���벶��֮*/

void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_timx_cap_chy_handle);
}


/* ��ʱ�����벶���жϴ���ص����� */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        if ((g_timxchy_cap_sta & 0X80) == 0)    /* ��û�гɹ����� */
        {
            if (g_timxchy_cap_sta & 0X40) /* �����½��� */
            {
                g_timxchy_cap_sta |= 0X80; /* ����һ�θߵ�ƽ */
                g_timxchy_cap_val = HAL_TIM_ReadCapturedValue(&g_timx_cap_chy_handle, TIM_CHANNEL_3);
                TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, TIM_CHANNEL_3);  /* ���ԭ������*/
                TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, TIM_CHANNEL_3, TIM_ICPOLARITY_RISING);
            }
            else /* ��δ��ʼ,��һ�β��������� */
            {
                g_timxchy_cap_sta = 0;
                g_timxchy_cap_val = 0;
                g_timxchy_cap_sta |= 0X40;    /* ���������� */
                __HAL_TIM_DISABLE(&g_timx_cap_chy_handle);
                __HAL_TIM_SET_COUNTER(&g_timx_cap_chy_handle, 0);
                TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, TIM_CHANNEL_3); /*���ԭ������*/
                TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, TIM_CHANNEL_3, TIM_ICPOLARITY_FALLING);
                __HAL_TIM_ENABLE(&g_timx_cap_chy_handle);
            }
        }
    }
}

/* ��ʱ�������жϻص����� */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        if ((g_timxchy_cap_sta & 0X80) == 0)/* ��δ�ɹ����� */
        {
            if (g_timxchy_cap_sta & 0X40) /* ����ߵ�ƽ*/
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
                    g_timxchy_cap_sta++;/*�������*/
                }
            }
        }
    }
}

