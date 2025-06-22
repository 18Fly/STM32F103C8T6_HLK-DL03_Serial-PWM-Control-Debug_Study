#ifndef __MPU6050_H_
#define __MPU6050_H_

#include "MyI2C.h"
#include "MPU6050_Reg.h"

/**
 * @brief MPU6050-往对应寄存器去发送1字节信息
 *
 * @param RegAddress 寄存器1字节地址
 * @param Data 1字节需发送的信息
 */
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data);

/**
 * @brief MPU6050-从对应寄存器读取1字节信息
 *
 * @param RegAddress 寄存器1字节地址
 * @return uint8_t 响应到的1字节信息
 */
uint8_t MPU6050_ReadByte(uint8_t RegAddress);

/**
 * @brief MPU6050六轴姿态传感器-初始化
 *
 */
void MPU6050_Init(void);

/**
 * @brief MPU6050六轴姿态传感器-获取加速度、陀螺仪数据
 *
 * @param Accel 二重指针-指向一个存有int16_t类型指针的数组-数组元素分别是X、Y、Z三个轴的加速度数据
 * @param Gyro 二重指针-指向一个存有int16_t类型指针的数组-数组元素分别是X、Y、Z三个轴的陀螺仪数据
 */
void MPU6050_GetData(int16_t **Accel, int16_t **Gyro);

#endif // !__MPU6050_H_
