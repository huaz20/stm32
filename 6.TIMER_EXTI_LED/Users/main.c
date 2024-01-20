#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/TIMER/timer.h"


int main(void)
{
    HAL_Init();                         /* ��ʼ��HAL�� */
    SystemClock_Config();   /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
    led_init();                         /* LED��ʼ�� */
	  btim_timx_int_init(10000-1,7200-1);
    while(1)
    { 
				
    }
}



