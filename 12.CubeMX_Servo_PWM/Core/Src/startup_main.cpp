#include "startup_main.h"
#include "tim.h"
#include "bsp_delay.h"


void startup_main(void)
{

		bsp_delay.f1.Init(72);
	
	  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
	
	
	
#if isRTOS==0    	//如果是裸机开发
	for(;;)  //等同于while(true)
	{
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,1850);/*90*/
				
				//HAL_Delay(2000);
				HAL_Delay(2000);
				__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,1750);/*180*/
				
				HAL_Delay(2000);
	}
#endif
}