/**
  ******************************************************************************
  * @file   Service_Devices.cpp
  * @brief  Devices service running file.
  ******************************************************************************
  * @note
  *  - Before running your devices, just do what you want ~ !
  *  - More devices or using other classification is decided by yourself ~ !
  ===============================================================================
                                    Task List
  ===============================================================================
  * <table>
  * <tr><th>Task Name     <th>Priority          <th>Frequency/Hz    <th>Stack/Byte
  * <tr><td>              <td>                  <td>                <td>    
  * </table>
  *
 */
/* Includes ------------------------------------------------------------------*/
#include "Service_Devices.h"
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
TaskHandle_t DeviceIMU_Handle;
TaskHandle_t UsartTx_Handle;

/* Private function declarations ---------------------------------------------*/
void Device_IMU(void *arg);
void Device_Usart(void *arg);


/* Exported devices ----------------------------------------------------------*/
/* Motor & ESC & Other actuators*/
/* Remote control */

/* IMU & NUC & Other sensors */

/* Other boards */

/* Function prototypes -------------------------------------------------------*/
/**
* @brief  Initialization of device management service
* @param  None.
* @return None.
*/
void Service_Devices_Init(void)
{
	xTaskCreate(Device_IMU,							"Dev.IMU", 					Large_Stack_Size,    NULL, PriorityAboveNormal, 		&DeviceIMU_Handle);
	xTaskCreate(Device_Usart,						"Dev.Usart", 				Small_Stack_Size,    NULL, PrioritySuperHigh, 			&UsartTx_Handle);
}

/**
 *@brief IMU数据更新任务
 */ 
void Device_IMU(void *arg)
{
  /* Cache for Task */
  TickType_t xLastWakeTime_t = xTaskGetTickCount();
	TickType_t _xTicksToWait = pdMS_TO_TICKS(2);
  /* Pre-Load for task */
	uint16_t count = 0;
  /* Infinite loop */
  for(;;)
  {
		/* 更新IMU数据 */
		imu.Update();
		count = (count + 1) % 200;
		if(!count) HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		
//		/* 判断是否进行控制 */
//		if()
		vTaskDelayUntil(&xLastWakeTime_t, _xTicksToWait);	
	}
}

void Device_Usart(void *arg)
{
  /* Cache for Task */
  TickType_t xLastWakeTime_t = xTaskGetTickCount();
	TickType_t _xTicksToWait = pdMS_TO_TICKS(500);
  /* Pre-Load for task */
	uint8_t res = 0;
  /* Infinite loop */
  for(;;)
  {
//		/* 发送数据 */
//		if(xQueueReceive(USART_TxPort,&res,portMAX_DELAY) == pdPASS)
//		{
//			HAL_UART_Transmit_DMA(&huart1,&res,1);
//		}
		res = (res+1) % 10;
		HAL_UART_Transmit_DMA(&huart1,&res,1);
		vTaskDelayUntil(&xLastWakeTime_t, _xTicksToWait);	
	}	
}


/* User Code End Here ---------------------------------*/

/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/
