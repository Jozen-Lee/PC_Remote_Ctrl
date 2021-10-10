/**
  ******************************************************************************
  * Copyright (c) 2021 - ~, TuTu Studio
  * @file    pose_cal.cpp
  * @author  LJY 2250017028@qq.com
  * @brief   Code for .
  * @date    2021-10-10
  * @version 1.0
  * @par Change Log:
  * <table>
  * <tr><th>Date        <th>Version  <th>Author     <th>Description
  * <tr><td>2021-10-10  <td> 1.0     <td>TuTu  			<td>Creator
  * </table>
  *
  ==============================================================================
                              How to use this driver  
  ==============================================================================
    @note
      -# 初始化
		 
    @warning	
      -# 
	  
  ******************************************************************************
  * @attention
  * 
  * if you had modified this file, please make sure your code does not have many 
  * bugs, update the version Number, write dowm your name and the date, the most
  * important is make sure the users will have clear and definite understanding 
  * through your new brief.
  *
  * <h2><center>&copy; Copyright (c) 2021 - ~,TuTu Studio.
  * All rights reserved.</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "pose_cal.h"
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
Pose_Cal imu_cal(&imu);
/* Private type --------------------------------------------------------------*/
/* Private function declarations ---------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
 *@brief 根据IMU数据输入控制信号,用于俄罗斯方块游戏
 */ 
void Pose_Cal::Tetris_AngleCtrl(QueueHandle_t send_queue)
{
	uint8_t num, signal;
	
//	// 右移
//	num = 0;
//	signal = DIR_RIGHT;
//	if(p_imu->data.pos.pitch > 20.f &&  p_imu->data.pos.pitch < 35.f) num = 1;
//	else if(p_imu->data.pos.pitch >= 35.f &&  p_imu->data.pos.pitch < 55.f) num = 2;
//	else if(p_imu->data.pos.pitch >= 55.f &&  p_imu->data.pos.pitch < 90.f) num = 3;
//	while(num--) xQueueSend(send_queue, &signal, 0);
//	
//	// 左移
//	num = 0;
//	signal = DIR_LEFT;
//	if(p_imu->data.pos.pitch < -20.f &&  p_imu->data.pos.pitch > -35.f) num = 1;
//	else if(p_imu->data.pos.pitch <= -35.f &&  p_imu->data.pos.pitch > -55.f) num = 2;
//	else if(p_imu->data.pos.pitch <= -55.f &&  p_imu->data.pos.pitch < -90.f) num = 3;
//	for(int i = 0; i < num; i ++) xQueueSend(send_queue, &signal, 0);	
	
	// 右移
	if(p_imu->data.pos.pitch > 20.f &&  p_imu->data.pos.pitch < 80.f)
	{
		signal = DIR_RIGHT;
		xQueueSend(send_queue, &signal, 0);
	}
	
	// 左移
	else if(p_imu->data.pos.pitch < -20.f &&  p_imu->data.pos.pitch > -80.f)
	{
		signal = DIR_LEFT;
		xQueueSend(send_queue, &signal, 0);
	}
	
	// 姿态变换
	if(p_imu->data.pos.roll < -15.f && p_imu->data.pos.roll > -80.f) 
	{
		signal = DIR_UP;
		xQueueSend(send_queue, &signal, 0);
	}
	
	// 加速下落
	else if(p_imu->data.pos.roll > 20.f && p_imu->data.pos.roll < 80.f) 
	{
		signal = DIR_DOWN;
		xQueueSend(send_queue, &signal, 0);
	}	
}

	/************************ COPYRIGHT(C) TuTu Studio **************************/
