/**
  ******************************************************************************
  * @file    srml_config_template.h
  * @brief   SRML configuration template file.
  *          This file should be copied to the application folder and renamed
  *          to srml_config.h.
  * @version 0.0.1
  ******************************************************************************
  * MOST IMPORTANTLY, this library is not open source for developers from other
  * schools' robot team currently. Plz make sure your code is under your supervision.
  *
  * Thank for @mannychen @HuanpengLu and other pioneers who have put forward such
  * architechure, and the endeavors of all developers.
  *
  * By downloading, copying, installing or using the software you agree to this license.
  * If you do not agree to this license, do not download, install,
  * copy or use the software.
  *
  *                          License Agreement
  *                For SCUT RobotLab Middleware Layer Library
  *
  * Copyright (c) 2019 - ~, SCUT RobotLab Development Team, all rights reserved.
  */

#ifndef __TSML_CONFIG_H__
#define __TSML_CONFIG_H__

/* ########################## Module Selection ############################## */
/**
  * @brief This is the list of modules to be used in the SRML.
  *        Change the value to 1 to use it.
  */

/* Drivers ----------------------------------------------------*/
#define USE_TWML_BMP280                     0
#define USE_TWML_BME280                     0
#define USE_TWML_FLASH                      0
#define USE_TSML_IMU                        1
#define USE_TSML_MT9V032                    0
#define USE_TSML_SDCARD                     0
#define USE_TSML_SERVO                      0
#define USE_TSML_SK6812                     0
#define USE_TSML_KEY                        0
#define USE_TSML_INFRARED                   0
  
#define USE_TSML_I2C                        1
#define USE_TSML_SPI                        0


/* Middlewares -----------------------------------------------*/
#define USE_TSML_DMP                        0
#define USE_TSML_MPL                        0
#define USE_TSML_FILTERS                    0
#define USE_TSML_KALMAN                     0
#define USE_TSML_INS                        0
#define USE_TSML_INTERGRAL                  0
  
#define USE_TSML_LAB_UM                     0
#define USE_TSML_ANO_UM                     0

/* Includes ------------------------------------------------------------------*/
/**
  * @brief Include module's header file
  */

/* Drivers ----------------------------------------------------*/

/* Devices header begin */
#if USE_TSML_BMP280
#include "Drivers/Devices/Barometer/BMP280/bmp280.h"
#endif
#if USE_TSML_BME280
#include "Drivers/Devices/Barometer/BME280/bme280_app.h"
#endif
#if USE_TSML_FLASH
#include "Drivers/Devices/FLASH/flash.h"
#endif
#if USE_TSML_IMU
#include "Drivers/Devices/IMU/imu.h"
#endif
#if USE_TSML_MT9V032
#include "Drivers/Devices/MT9V034/MT9V032.h"
#endif
#if USE_TSML_SDCARD
#include "Drivers/Devices/SDcard/SDcard.h"
#endif
#if USE_TSML_SERVO
#include "Drivers/Devices/Servo/Servo.h"
#endif
#if USE_TSML_SK6812
#include "Drivers/Devices/SK6812/sk6812.h"
#endif
#if USE_TSML_KEY
#include "Drivers/Devices/KEY/key.h"
#endif
#if USE_TSML_INFRARED
#include "Drivers/Devices/Infrared/infrared.h"
#endif
/* Devices header end */

/* Components header begin */
#if USE_TSML_I2C
#include "Drivers/Components/I2C/tutu_drv_i2c.h"
#endif
#if USE_TSML_SPI
#include "Drivers/Components/SPI/tutu_driver_spi.h"
#endif
/* Components header end */


/* Middlewares -----------------------------------------------*/

/* Algorithms header begin */
#if USE_TSML_DMP
#include "Middlewares/Algorithm/DMP/dmp_cal.h"
#endif
#if USE_TSML_MPL
#include "Middlewares/Algorithm/MPL/mpl_cal.h"
#endif
#if USE_TSML_FILTERS
#include "Middlewares/Algorithm/Filters/tutu_filters.h"
#endif
#if USE_TSML_KALMAN
#include "Middlewares/Algorithm/Kalman/kalman.h"
#endif
#if USE_TSML_INS
#include "Middlewares/Algorithm/INS/ins.h"
#endif
#if USE_TSML_INTERGRAL
#include "Middlewares/Algorithm/Intergral/integral_algorithm.h"
#endif
/* Algorithms header end */

/* UpperMonitor header begin */
#if USE_TSML_LAB_UM
#include "Middlewares/UpperMonitor/SCUT_LAB/UpperMonitor.h"
#endif
#if USE_TSML_ANO_UM
#include "Middlewares/UpperMonitor/ANO/Ano_UpperMonitor.h"
#endif
/* UpperMonitor header end */


#endif /* __SRML_CONFIG_H__ */

/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/
