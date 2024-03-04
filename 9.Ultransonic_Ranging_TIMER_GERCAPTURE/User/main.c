#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/TIMER/gtim.h"

extern uint8_t g_timxchy_cap_sta ;/*���벶��״̬*/
extern uint16_t g_timxchy_cap_val;/*���벶��֮*/

uint32_t temp = 0;
uint32_t distance = 0;

int main(void)
{
    HAL_Init();                                 /* ��ʼ��HAL�� */
    SystemClock_Config();        /* ����ʱ��,72M */
    delay_init(72);                             /* ��ʼ����ʱ���� */
    led_init();                                /* ��ʼ��LED */
    gtim_timx_cap_chy_init(0XFFFF,72 - 1);
    while(1)
    {
				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,GPIO_PIN_SET);
				delay_us(11);
				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,GPIO_PIN_RESET);
				delay_ms(100);
				if(g_timxchy_cap_sta  &  0X80)
				{
					temp = g_timxchy_cap_sta  & 0X3F;
					temp *= 65536;
					temp += g_timxchy_cap_val;
					distance = temp * 1000000 / 340;
				}
	}
}
