/**
  ******************************************************************************
  * Copyright (c) 2019 - ~, SCUT-RobotLab Development Team
  * @file    srml_std_lib.h
  * @author  EnnisKoh 8762322@qq.com
  * @brief   收容各种难以收容但又需要统一标准的东西
  * @date    2021-04-29
  * @version 1.1
  *
  ******************************************************************************
  * @attention
  *
  * if you had modified this file, please make sure your code does not have many
  * bugs, update the version Number, write dowm your name and the date, the most
  * important is make sure the users will have clear and definite understanding
  * through your new brief.
  *
  * <h2><center>&copy; Copyright (c) 2019 - ~, SCUT-RobotLab Development Team.
  * All rights reserved.</center></h2>
  ******************************************************************************
  */

#ifndef _SRML_STD_LIB_H_
#define _SRML_STD_LIB_H_

#ifdef  __cplusplus
/* Includes ------------------------------------------------------------------*/
#include <cstdint>
#if defined(USE_HAL_DRIVER)
  #if defined(STM32F405xx) || defined(STM32F407xx)
    #include <stm32f4xx_hal.h>
  #endif
  #if defined(STM32F103xx)
    #include <stm32f1xx_hal.h>
  #endif
  #if defined(STM32H750xx)
    #include <stm32h7xx_hal.h>
  #endif
#endif
/* Private macros ------------------------------------------------------------*/
/* Private type --------------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

namespace std_lib
{
/* Exported variables --------------------------------------------------------*/

/* Exported function declarations --------------------------------------------*/
template<class T>
T constrain(T input,T min,T max)
{
  if (input <= min)
    return min;
  else if(input >= max)
    return max;
  return input;
}

uint16_t get_gpio_pin_num(uint16_t GPIO_Pin);
}

#endif /* __cplusplus */

#endif /* _SHIT_MOUNTAIN_H_ */

/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/
