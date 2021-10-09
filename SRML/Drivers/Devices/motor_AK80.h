/**
  ******************************************************************************
  * Copyright (c) 2019 - ~, SCUT-RobotLab Development Team
  * @file    Motor.h
  * @author  lindongdong  1027221389@qq.com 
  * @brief   Motro for RC_Dog
  *			     Currently motor type only supports haitai motor AK80-01-03
  * @date    2021-02-21
  * @attention
  * @note 
      
	AK80_V3使用方法：
	
      -1. 实例化AK80_V3类             如：AK80_V3 Motor_1(0x01,&hcan1);
      -2. 调用函数进入电机控制模式    如：Motor_1.To_Into_Control();
      -3. 设置电机零点(选做)          如：Motor_1.Set_ZeroPosition();
      -4. 在CAN中断中做数据结算       如：Motor_1.Update(CAN_RxMessage->data);
			-5. 扭矩、速度、位置控制电机    如：Out_Torque_Control(float torque);
		                                      Out_Speed_Control  (float speed, float kd );
		                                      Out_Position_Control(float position ,float kp);
		                                      Out_Mixed_Control (float position ,float kp ,float kd);
																				 
			注：主机ID默认为0x00，电机ID默认为0x01，电机ID可用上位机修改。
			
			
  AK80_V1使用方法：
			 
      -1. 实例化AK80_V1类             如：AK80_V3 Motor_2(0x01,&hcan1);
      -2. 调用函数进入位置、速度模式  如：Motor_2.To_Speed_Control();
		                                      Motor_2.To_Position_Control();
      -3. 保存设置                    如：Motor_2.Save();
      -4. 在CAN中断中做数据结算       如：Motor_2.Update(CAN_RxMessage->data);
			-5. 速度、位置控制电机          如：Motor_2.Out_Speed(int16_t speed);
		                                      Motor_2.Out_Position(int16_t acceleration,int16_t speed,int16_t position);
																					
			注：主机ID默认为0xff，电机ID可用CAN发送相关指令修改，修改后重新上电后生效。如果不知道电机ID，可以用0x00登录修改ID
			
  ******************************************************************************
  */
#ifndef _MOTOR_H_
#define _MOTOR_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "Drivers/Components/drv_can.h"

#ifdef __cplusplus

/* Private define-------------------------------------------------------------*/

#define LIMIT_MIN_MAX(x,min,max) (x) = (((x)<=(min))?(min):(((x)>=(max))?(max):(x)))
#define ABS(x) ((x)>=0?(x):-(x))
/* Private Enum---------------------------------------------------------------*/

enum Control_State {
	EXIT_CONTROL =0,     /*退出电机控制模式*/
	INTO_CONTROL =1,     /*电机预控制模式  */
	CURRENT_CONTROL=2,   /*电流环控制      */ 
	SPEED_CONTROL =3,    /*速度单环控制(Kd)*/
	POSITION_CONTROL =4, /*位置单环控制(Kd)*/
	MIXED_CONTROL =5,    /*双环控制(Kp、Kd)*/
	WARNING=6            /*警告未进入电机控制模式*/
};



/**
  @brief class for motors AK80_V3.
*/
class AK80_V3
{
public:
    AK80_V3(uint16_t id ,CAN_HandleTypeDef* hcan) {ID=id; Can=hcan;}
    ~AK80_V3(){}
		CAN_HandleTypeDef* Can;
		virtual bool CheckID(uint16_t StdID) const { return StdID == (uint16_t)ID; }
    uint16_t ID = 0;
		Control_State Current_mode = EXIT_CONTROL;
	  float Command_Position = 0.0f;
		float Command_Speed = 0.0f;
		float Command_Torque = 0.0f;
	  float Command_Kp =0.0f;
		float Command_Kd =0.0f;
		
		float get_current_angle(){return this->Current_Angle;}
		float get_current_position(){return this->Current_Position;}
			
		void Update(uint8_t can_rx_data[]);
		void Set_ZeroPosition();
		void To_Exit_Control();
		void To_Into_Control();
			
		void Out_Torque_Control(float torque);
		void Out_Speed_Control  (float speed, float kd );
		void Out_Position_Control(float position ,float kp);
		void Out_Mixed_Control (float position ,float speed,float kp ,float kd);
			
private:
	  float Current_Position = 0.0f;  //(rad) 
		float Current_Speed = 0.0f;     //(rad/s)
		float Current_Torque= 0.0f;     //(Nm)

    float Current_Angle = 0.0f;     //(° )
    float Current_Rpm = 0.0f;       //(圈/s)

    float POSITION_MAX() const { return 95.5f ;}
		float POSITION_MIN() const { return -95.5f;}
		float SPEED_MAX()    const { return 30.0f ;}
		float SPEED_MIN()    const { return -30.0f;}
		float KP_MAX()       const { return 500.0f;}
		float KP_MIN()       const { return 0.0f  ;}
		float KD_MAX()       const { return 5.0f  ;}
	  float KD_MIN()       const { return 0.0f  ;}
		float TORQUE_MAX()   const { return 18.0f ;}
		float TORQUE_MIN()   const { return -18.0f;}
		
		void Out (float current,float speed,float position,float kp ,float kd);
		
		float uint_to_float(int x_int, float x_min, float x_max, int bits);
		uint16_t float_to_uint(float x, float x_min, float xmax, uint8_t bits);
		
};


class AK80_V1
{
public:
    AK80_V1(uint16_t id ,CAN_HandleTypeDef* hcan) {Slave_Address=id; Can=hcan;}
    ~AK80_V1(){}
		CAN_HandleTypeDef* Can;
		uint8_t Host_Address =0xff;//主机ID
		uint8_t Slave_Address=0x00;//从机ID 
		Control_State Current_State =INTO_CONTROL;
		
		int16_t Command_Acceleration =0;//(rpm/s)
		int16_t Command_Speed =0;       //(rpm)
		uint16_t Command_Position =0;   //(0~36000)
		uint16_t Command_Angle=0;       //(0~360°)
		
		void Update(uint8_t can_rx_data[]);
		void Modify_Slave_Address(uint8_t slave_address);
		void Read_Temperature();
    void To_Speed_Control();
		void To_Position_Control();
		void Out_Speed(int16_t speed);
		void Out_Position(int16_t acceleration,int16_t speed,int16_t position);
			
private:
	  int16_t  Current_Torque =0;  //(N·m)
    int16_t  Current_Speed =0;   //(rpm)
    uint16_t Current_Position=0; //(0~36000)
    uint16_t Current_Angle =0;   //(0~360°)
    uint8_t  Current_Temperature=0;//(0~100℃)

    uint16_t POSITION_MAX() const { return 36000;}
		uint16_t POSITION_MIN() const { return 0    ;}
		int16_t SPEED_MAX()    const { return  256 ;}
		int16_t SPEED_MIN()    const { return -256 ;}
//		int16_t TORQUE_MAX()   const { return  ;} 
//		int16_t TORQUE_MIN()   const { return  ;}
};


#endif
#endif
/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/
	
	
	
	
	
	
	
	
	
	
	
