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
#include "pose_cal.h"
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
TaskHandle_t DeviceIMU_Handle;
TaskHandle_t UsartTx_Handle;
TaskHandle_t AngleCtrl_Handle;
TaskHandle_t AccCtrl_Handle;
/* Private function declarations ---------------------------------------------*/
void Device_IMU(void *arg);
void Device_Usart(void *arg);
void AngleCtrl_Task(void *arg);
void AccCtrl_Task(void *arg);
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
	xTaskCreate(Device_Usart,						"Dev.Usart", 				Small_Stack_Size,    NULL, PriorityHigh, 			&UsartTx_Handle);
	xTaskCreate(Device_IMU,							"Dev.IMU", 					Large_Stack_Size,    NULL, PriorityNormal, 						&DeviceIMU_Handle);
//	xTaskCreate(AngleCtrl_Task,					"Ctrl.Angle", 			Small_Stack_Size,    NULL, PriorityHigh, 							&AngleCtrl_Handle);
//	xTaskCreate(AccCtrl_Task,						"Ctrl.Acc", 				Small_Stack_Size,    NULL, PrioritySuperHigh, 			&AccCtrl_Handle);
}

/**
 *@brief IMU数据更新任务
 */ 
void Device_IMU(void *arg)
{
  /* Cache for Task */
  TickType_t xLastWakeTime_t = xTaskGetTickCount();
	TickType_t _xTicksToWait = pdMS_TO_TICKS(4);
  /* Pre-Load for task */
	uint16_t count = 0;
  /* Infinite loop */
  for(;;)
  {
		// 更新IMU数据 
		imu.Update();
		
		// 输出控制数据 
		imu_cal.Tetris_AngleCtrl(USART_TxPort);
		
		// 用于指示任务正常执行
		count = (count + 1) % 100;
		if(!count) HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	
		
		vTaskDelayUntil(&xLastWakeTime_t, _xTicksToWait);	
	}
}

/**
 *@brief 串口发送任务
 */ 
void Device_Usart(void *arg)
{
  /* Cache for Task */
  /* Pre-Load for task */
	uint8_t res = 0;
  /* Infinite loop */
  for(;;)
  {
		/* 发送数据 */
		if(xQueueReceive(USART_TxPort,&res,portMAX_DELAY) == pdPASS)
		{
//			HAL_UART_Transmit(&huart1,&res,1, 10);
			HAL_UART_Transmit_DMA(&huart1,&res,1);
		}
	}	
}

/**
 *@brief 角度控制任务
 */ 
void AngleCtrl_Task(void *arg)
{
  /* Cache for Task */
  TickType_t xLastWakeTime_t = xTaskGetTickCount();
	TickType_t _xTicksToWait = pdMS_TO_TICKS(50);
  /* Pre-Load for task */
  /* Infinite loop */
  for(;;)
  {
		
		vTaskDelayUntil(&xLastWakeTime_t, _xTicksToWait);	
	}	
}

/* User Code End Here ---------------------------------*/

/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/
