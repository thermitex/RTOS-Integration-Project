/****************************************************************************
 *  Copyright (C) 2018 RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/
/** @file bsp_can.h
 *  @version 1.0
 *  @date Apr 2017
 *
 *  @brief receive external can device message
 *
 *  @copyright 2017 DJI RoboMaster. All rights reserved.
 *
 */
	
#ifndef __BSP_CAN_H__
#define __BSP_CAN_H__

#include "can.h"

/* CAN send and receive ID */
typedef enum
{
  CAN_3510_M1_ID       = 0x201,
  CAN_3510_M2_ID       = 0x202,
  CAN_3510_M3_ID       = 0x203,
  CAN_3510_M4_ID       = 0x204,
  CAN_YAW_MOTOR_ID     = 0x205,
  CAN_PIT_MOTOR_ID     = 0x206, 
  CAN_TRIGGER_MOTOR_ID = 0x207,
  CAN_CHASSIS_ZGYRO_ID = 0x401,
  CAN_GIMBAL_ZGYRO_ID  = 0x402,

  CAN_ZGYRO_RST_ID     = 0x406,
  CAN_CHASSIS_ALL_ID   = 0x200,
  CAN_GIMBAL_ALL_ID    = 0x1ff,

} can_msg_id_e;

/* can receive motor parameter structure */
#define FILTER_BUF 5
typedef struct
{
  uint16_t ecd;
  uint16_t last_ecd;
  
  int16_t  speed_rpm;
  int16_t  given_current;

  int32_t  round_cnt;
  int32_t  total_ecd;
  int32_t  total_angle;
  
  uint16_t offset_ecd;
  uint32_t msg_cnt;
  
  int32_t  ecd_raw_rate;
  int32_t  rate_buf[FILTER_BUF];
  uint8_t  buf_cut;
  int32_t  filter_rate;
} moto_measure_t;

/*
typedef struct Can
{
	CAN_TxHeaderTypeDef canTxHeader;
	
	uint32_t StdId;
	uint32_t IDE;
	uint32_t RTR;
	uint32_t DLC;
	uint32_t rx_StdId;
	uint8_t* data;
	int rx_buffer_size;
} Can;

void Device_Initialize(Can* device,const uint32_t StdId, const uint32_t IDE, const uint32_t RTR, const uint32_t DLC, const uint32_t rx_StdId, const int rx_buffer_size);
void Can_Transmit(Can* device,CAN_HandleTypeDef* hcan,uint8_t* canMsg);
void Can_Receive(CAN_HandleTypeDef* hcan, uint8_t* canRxMsg);
void Device_Activate_Rx(Can* device);
//void test_smart_can(Can* device, CAN_HandleTypeDef* hcan,int16_t cm1_iq,int16_t cm2_iq,int16_t cm3_iq,int16_t cm4_iq);
void Device_ResizeRxBuffer(Can* device, int rx_buffer_size);

/*#define SPEED_OUTPUT_ATTENUATION (1.0f)
#define RATE_BUF_SIZE 6
typedef struct{
	int32_t raw_value; 
	int32_t last_raw_value;	
	int32_t ecd_value; 
	int32_t diff;	
	int32_t temp_count; 
	uint8_t buf_count;
	int32_t ecd_bias;				
	int32_t ecd_raw_rate;						
	float rate_buf[RATE_BUF_SIZE];
	int32_t round_cnt;	
	int32_t filter_rate;											
	float ecd_angle;				
	float last_ecd_angle;
	float ecd_speed;
}Encoder;*/

extern moto_measure_t moto_chassis[];
extern moto_measure_t moto_yaw, moto_pit, moto_trigger;
//extern float          yaw_zgyro_angle;

void encoder_data_handler(moto_measure_t* ptr, CAN_HandleTypeDef* hcan);
void get_moto_offset(moto_measure_t* ptr, CAN_HandleTypeDef* hcan);

void can_device_init(void);
void can_receive_start(void);

void gyro_device_init(void);
void send_gimbal_cur(int16_t yaw_iq, int16_t pit_iq, int16_t trigger_iq);
void send_chassis_cur(int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4);
#endif
