/**
  ******************************************************************************
  * Copyright (c) 2021 - ~, TuTu Studio
	* @file    pose_cal.h
  * @author  LJY 2250017028@qq.com
  * @brief   Code for calculate imu pose to put out control signal.
  ******************************************************************************
  * @attention
  * 
  * if you had modified this file, please make sure your code does not have many 
  * bugs, update the version Number, write dowm your name and the date, the most
  * important is make sure the users will have clear and definite understanding 
  * through your new brief.
  *
  * <h2><center>&copy; Copyright (c) 2021 - ~, TuTu Studio.
  * All rights reserved.</center></h2>
  ******************************************************************************
  */ 

#ifndef __POSE_CAL_H_
#define __POSE_CAL_H_

#ifdef __cplusplus
 extern "C" {
#endif

#ifdef __cplusplus
}
#endif	

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/  
#include "System_DataPool.h"
/* Private define ------------------------------------------------------------*/
#define DIR_UP 		1
#define DIR_DOWN 	2 
#define DIR_LEFT	3
#define DIR_RIGHT 4				

/* Private include -----------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
	 
/* Private type --------------------------------------------------------------*/
	
/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
class Pose_Cal
{
public:
	Pose_Cal(IMU* imu)
	{
		p_imu = imu;
	}
	void Tetris_AngleCtrl(QueueHandle_t send_queue);
private:
	
	// 陀螺仪指针
	IMU* p_imu;

	// 输出的控制信号
	uint8_t angle_ctrl;
	uint8_t acc_ctrl;

	
};

/* Exported variables --------------------------------------------------------*/
extern Pose_Cal imu_cal;
/* Exported function declarations --------------------------------------------*/

#endif	/* __cplusplus */

#endif	/* define */
	/************************ COPYRIGHT(C) TuTu Studio **************************/
