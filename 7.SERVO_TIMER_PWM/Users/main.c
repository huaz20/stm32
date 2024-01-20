#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/TIMER/gtim.h"
#include "stm32f1xx_hal.h"

void led_init(void);                       /* LED??????? */

extern TIM_HandleTypeDef g_timx_pwm_chy_handle;

int main(void)
{
    HAL_Init();                         /*��ʼ��HAL��*/
    SystemClock_Config(); 					/* ʱ��72Mhz */
    delay_init(72);                    /*��ʱ������ʼ��*/ 
    led_init();                         /* LED��ʼ�� */
	  gtim_timx_pwm_chy_init(2000 - 1,720 - 1);  /*ͨ�ö�ʱ����ʼ��*/
    while(1)
    { 
			
				__HAL_TIM_SET_COMPARE(&g_timx_pwm_chy_handle,TIM_CHANNEL_3,1850);/*90*/
				delay_ms(2000);
				
				__HAL_TIM_SET_COMPARE(&g_timx_pwm_chy_handle,TIM_CHANNEL_3,1750);/*180*/
				delay_ms(2000);
				
    }
}

