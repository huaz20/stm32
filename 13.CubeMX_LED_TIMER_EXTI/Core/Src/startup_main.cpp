#include "startup_main.h"

extern TIM_HandleTypeDef htim1;

void startup_main(void)
{
		HAL_TIM_Base_Start_IT(&htim1);
	
#if isRTOS==0    	//������������
	for(;;)  //��ͬ��while(true)
	{
		
	}
#endif
}