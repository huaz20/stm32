#include "startup_main.h"

extern UART_HandleTypeDef huart1;
uint8_t g_rx_buffer[1];

void startup_main(void)
{

	
#if isRTOS==0    	//如果是裸机开发
	for(;;)  //等同于while(true)
	{
			HAL_UART_Receive_IT(&huart1, (uint8_t *)g_rx_buffer, 1);
				HAL_UART_Transmit(&huart1,(uint8_t*)g_rx_buffer,1,100);
			if(g_rx_buffer[0] == '1')
				 {
						  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
				 }
		 else if(g_rx_buffer[0] == '0')
				 {
							HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
				 }
				
	}
#endif
}