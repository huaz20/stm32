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
    HAL_Init();                         /*初始化HAL库*/
    SystemClock_Config(); 					/* 时钟72Mhz */
    delay_init(72);                    /*延时函数初始化*/ 
    led_init();                         /* LED初始化 */
	  gtim_timx_pwm_chy_init(2000 - 1,720 - 1);  /*通用定时器初始化*/
    while(1)
    { 
			
				__HAL_TIM_SET_COMPARE(&g_timx_pwm_chy_handle,TIM_CHANNEL_3,1850);/*90*/
				delay_ms(2000);
				
				__HAL_TIM_SET_COMPARE(&g_timx_pwm_chy_handle,TIM_CHANNEL_3,1750);/*180*/
				delay_ms(2000);
				
    }
}

