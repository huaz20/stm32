#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/TIMER/gtim.h"

extern uint8_t g_timxchy_cap_sta ;/*输入捕获状态*/
extern uint16_t g_timxchy_cap_val;/*输入捕获之*/

uint32_t temp = 0;
uint32_t distance = 0;

int main(void)
{
    HAL_Init();                                 /* 初始化HAL库 */
    SystemClock_Config();        /* 设置时钟,72M */
    delay_init(72);                             /* 初始化延时函数 */
    led_init();                                /* 初始化LED */
    gtim_timx_cap_chy_init(0XFFFF,72 - 1);
    while(1)
    {
				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,GPIO_PIN_SET);
				delay_us(11);
				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,GPIO_PIN_RESET);
				if(g_timxchy_cap_sta  &  0X80)
				{
					temp = g_timxchy_cap_sta  & 0X3F;
					temp *= 65536;
					temp += g_timxchy_cap_val;
					distance = temp * 1000000 / 340;
				}
	}
}
