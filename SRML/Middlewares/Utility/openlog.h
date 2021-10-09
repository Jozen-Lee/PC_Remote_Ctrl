/**
******************************************************************************
* Copyright (c) 2021 - ~, SCUT-RobotLab Development Team
* @file    openlog.h
* @author  Lutoo e19135693@163.com
* @brief   Header file of openlog driver.
* @date    2021-5-15
* @version 1.0
* @par Change Log：
* <table>
* <tr><th>Date        <th>Version  <th>Author    		<th>Description
* <tr><td>2021-05-15  <td> 1.0     <td>Lutoo	 	    <td>Creator
* </table>
*
*==============================================================================
					##### How to use this driver #####
==============================================================================
  @note
		please see https://git.scutbot.cn/WFshuli/openlog
******************************************************************************
* @attention
*
* if you had modified this file, please make sure your code does not have many
* bugs, update the version Number, write dowm your name and the date, the most
* important is make sure the users will have clear and definite understanding
* through your new brief.
*
* <h2><center>&copy; Copyright (c) 2021 - ~, SCUT-RobotLab Development Team.
* All rights reserved.</center></h2>
******************************************************************************
*/

#pragma once

#ifdef __cplusplus
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <string>
#include <stdarg.h>
#include <memory.h>
/* Private define ------------------------------------------------------------*/
#define OP_MAX_BUFFSIZE 256				//	openlog 最大缓存区大小
/* Exported types ------------------------------------------------------------*/
using op_user_transmit = uint32_t (*)(uint8_t *buf, uint16_t len);	//	openlog发送函数指针类型

/**
 * @brief <openlog> 打包数据推入缓存区的返回值
 */
typedef enum {
	OP_PACK_OK,
	OP_PACK_BUSY,
}OP_Pack_state;

/**
 * @brief <openlog> 发送数据许可类型
 */
typedef enum {
	OP_PERMIT_NULL,
	OP_PERMIT_WRITE,
	OP_PERMIT_ORDER
}OP_PERMIT;

/**
 * @brief <openlog>	接收数据类型
 */
typedef enum {
	OP_RX_NULL,
	OP_READ_SIZE
}OP_rxtype;
>>>>>>> stm32cubeide

/*
 * @brief multiple buff stream control
 */
template<uint8_t buff_N>
class OP_Buff_c
{
protected:
  char      log_array[buff_N][OP_MAX_BUFFSIZE];		//	日志缓存区数组
  char*  	cur_buff_addr = log_array[0];			//	目前要发送的数据地址
  char*  	pending_buff_addr = log_array[0];		//	目前要推入缓存区的地址
  uint16_t  buff_size[buff_N];						//	缓存区各个数据长度
  uint16_t  cur_buff_pos = 0;						// 	目前要发送的数据包在缓存区的排列位置
  uint16_t  pending_buff_num = 0;					//	缓存区等待发送的数据包数量
  uint16_t  pending_buff_pos = 0;					//	目前要推入缓存区的数据包在缓存区的排列位置
  op_user_transmit out = nullptr;					//	发送函数指针
public:
  /**
   * @brief constructor
   */
  OP_Buff_c(){}
  /**
   * @brief destructor
   */
  ~OP_Buff_c(){
	  memset(log_array,0, buff_N * OP_MAX_BUFFSIZE );
	  memset(buff_size,0, buff_N);
	  out = nullptr;
  }
  /*
   * @brief write the character to the current buff until finish or buff is full
   */
  void write_string(const char *_str){
	if(pending_buff_num == buff_N){return;}
    while(*_str != 0 && buff_size[cur_buff_pos] <= OP_MAX_BUFFSIZE){
    	cur_buff_addr[buff_size[cur_buff_pos] ++] = *_str++;
    }
  }
  template<typename ... Args>
  void write_string(const char *_str, Args& ...  args)
  {
    write_string(_str);
    write_string(args...);
  }
  /*
   * @brief write variable in hex
   */
  template<typename T>
  void write_hex(T t){
	  if(pending_buff_num == buff_N){return;}
      uint8_t size = sizeof(T)/sizeof(char);
      char *ptr = (char*)&t;
      while(size-- != 0 && buff_size[cur_buff_pos] <= OP_MAX_BUFFSIZE){
    	  cur_buff_addr[buff_size[cur_buff_pos] ++] = *ptr++;
      }
  }
  /*
   * @brief turn the current buff to the next buff
   */
  void turn_buff(){
	  if(cur_buff_pos < buff_N-1){cur_buff_pos++;}
	  else{cur_buff_pos = 0;}
	  buff_size[cur_buff_pos] = 0;
	  cur_buff_addr = log_array[cur_buff_pos];
  }
  /*
   * @brief check pending buff to send
   */
  uint16_t check_pending_buff(OP_PERMIT &_permission){
	  if(pending_buff_num > 0 && _permission !=OP_PERMIT_NULL){
		  if(out != NULL){
			  _permission = OP_PERMIT_NULL;
			  out((uint8_t*)pending_buff_addr,buff_size[pending_buff_pos]);}
		  pending_buff_num--;
		  if(pending_buff_pos < buff_N-1){pending_buff_pos++;}
		  else{pending_buff_pos = 0;}
		  pending_buff_addr = log_array[pending_buff_pos];
	  }
	  return pending_buff_num;
  }
  /*
   * @brief pack the current buff
   */
  OP_Pack_state Pack(OP_PERMIT &_permission){
	  	if(pending_buff_num == buff_N){return OP_PACK_BUSY;}
	  	else if(pending_buff_num == 0){
	  		pending_buff_addr = cur_buff_addr;
	  		pending_buff_pos  = cur_buff_pos;
	  		pending_buff_num++;
	  		if(out != NULL && _permission !=OP_PERMIT_NULL){
	  			_permission = OP_PERMIT_NULL;
	  			pending_buff_num--;
	  			out((uint8_t*)pending_buff_addr,buff_size[pending_buff_pos]);
	  		}
	  	}
	  	else{pending_buff_num++;}
	  	turn_buff();
  		return OP_PACK_OK;
  	}
};

/*
 * @brief openlog class
 */
template<uint8_t buff_N>
class openlog_c : public OP_Buff_c<buff_N>{
private:
	uint32_t file_size;							// 	操作文件大小
	OP_PERMIT permission = OP_PERMIT_NULL;		//	发送（文件操作）许可
	OP_rxtype rxtype;							//	接收数据类型
	/*
	 * @brief turn the num in str to unsigned int (only for openlog)
	 */
	uint8_t str2ui(const uint8_t* buf){
		uint16_t pos = 0;
		uint16_t size = 0;
		if(*buf < 0x30 || *buf > 0x39){return 1;}
		while(*(buf + pos) != '\r'){
			size *= 10;
			size += *(buf + pos ) - 0x30;
			pos++;
		}
		file_size = size;
		return 0;
	}

	/**
	 * @brief	格式化记录字符串
	 * @param	format	格式化字符串
	 * @param	_args	可变参数列表
	 */
	void record_format(const char *format,va_list _args){
		if(this->pending_buff_num == buff_N){return;}
		this->buff_size[this->cur_buff_pos] +=
				vsnprintf(this->cur_buff_addr + this->buff_size[this->cur_buff_pos],
							OP_MAX_BUFFSIZE - this->buff_size[this->cur_buff_pos],
							format,_args);
		}
public:
	/**
	 * @brief 	Constructor
	 * @func	断言buff_N是否符合范围要求
	 */
	openlog_c():OP_Buff_c<buff_N>(){static_assert((buff_N>0)&&(buff_N<=16),"openlog buff number should be in [1,16]");}

	/**
	 * @brief 	注册发送函数
	 * @param	_func	发送函数指针
	 */
	inline void user_tx_register(op_user_transmit _func){this->out = _func;}

	/**
	 * @brief 	获取文件大小
	 */
	inline uint32_t get_file_size(){return this->file_size;}

	/**
	 * @brief	清空当前操作的缓存区
	 */
	inline void clear_buff(){this->buff_size[this->cur_buff_pos] = 0;}

	/*
	 * @brief 	将数据包推入缓存区等待发送
	 */
	inline OP_Pack_state Send(){return this->Pack(permission);}

	/*
	 * @brief 	串口回调函数.
	 * @param	RxData	接收数据的首地址
	 * @param	RxLen	接收数据长度
	 * @warning 请不要将这个函数直接在串口初始化函数中注册为回调函数.
>>>>>>> stm32cubeide
	 */
	uint32_t OP_RXcallback(uint8_t *RxData, uint16_t RxLen)
	{
	  uint8_t& end_char = *(RxData + RxLen - 1 );
	  if(end_char == '<'){
		  permission = OP_PERMIT_WRITE;
	  }
	  else if(end_char == '>'){
		  permission = OP_PERMIT_ORDER;
		  if(rxtype == OP_READ_SIZE && str2ui(RxData) == 0){
			  rxtype = OP_RX_NULL;
		  }
	  }
	  else{permission = OP_PERMIT_NULL;}
	  this->check_pending_buff(permission);
	  return 0;
	}
// these are the functions to operate file_system or record bellow -----------------------

	/**
	 * @brief 		openlog 系统硬件初始化
	 * @atention	openlog 系统开机就会自动初始化
	 */
	void hadware_init(void)					{this->write_string("init\r");}

	/**
	 * @brief 		openlog	系统硬件复位
	 */
	void hardware_reset(void)				{this->write_string("reset\r");}

	/**
	 * @brief		新建文件
	 * @param		filename	文件名字
	 */
	void new_file(const char* filename)		{this->write_string("new ",filename,"\r");}

	/**
	 * @brief		新建文件
	 * @param		filename	文件名字
	 * @param		...			可变参数
	 */
	void new_file(const char* filename,...){
		va_list args;
		va_start(args,filename);
		this->write_string("new ");
		record_format(filename, args);
		va_end(args);
		this->write_string("\r");
	}

	/**
	 * @brief		新建文件夹
	 * @param		subdirectory	文件夹名
	 */
	void md(const char* subdirectory)		{this->write_string("md ",subdirectory,"\r");}

	/**
	 * @brief		移动到对应文件夹
	 * @param		subdirectory	文件夹名	可以为".." 表示退回上一级文件夹
	 */
	void cd(const char* subdirectory)		{this->write_string("cd ",subdirectory,"\r");}

	/**
	 * @brief		读文件大小
	 * @param		filename	文件名
	 * @param		...			可变参数
	 */
	void read_file_size(const char* filename,...){
		va_list args;
		va_start(args,filename);
		this->write_string("size ");
		record_format(filename,args);
		va_end(args);
		this->write_string("\r");
		rxtype = OP_READ_SIZE;
	}

	/**
	 * @brief		覆盖文件
	 * @param		offset		覆盖写起始位置
	 * @param		filename	文件名
	 * @param		...			可变参数
	 */
	OP_rxtype write_file(uint16_t offset,const char* filename,...){
		va_list args;
		va_start(args,filename);
		this->write_string("write ");
		record_format(filename, args);
		va_end(args);
		record_format(" %d", offset);
		this->write_string("\r");
		return rxtype;
	}

	/**
	 * @brief 		进入命令行模式 ，换句话就是退出写文件模式
	 */
	void enterCommandMode(void){
		char com[3]={0x1A,0x1A,0x1A};
		this->write_string(com,"\r");
	}

	/**
	 * @brief		记录字符串到文件中
	 * @param		str		需要写入的字符串
	 */
	void record(const char *str){this->write_string(str);}

	/**
	 * @brief 		格式化记录字符串到文件中
	 * @param		format		格式化字符串
	 * @param		...			可变参数
	 */
>>>>>>> stm32cubeide
	void record_format(const char *format,...){
		va_list args;
		va_start(args,format);
		record_format(format,args);
		va_end(args);
	}

	/**
	 * @brief	以16进制格式记录到文件中
	 */
	template<typename T,typename ... Args>
	void recore_hex(T &t,Args... args){
		write_hex(t);
		write_hex(args...);
	}
};
#endif
/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/
