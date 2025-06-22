#include "MPU6050.h"

#define MPU6050_ADDR 0xD0

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDR);
    MyI2C_ReadAck();
    MyI2C_SendByte(RegAddress);
    MyI2C_ReadAck();
    MyI2C_SendByte(Data);
    MyI2C_ReadAck();
    MyI2C_Stop();
}

uint8_t MPU6050_ReadByte(uint8_t RegAddress)
{
    uint8_t Data;
    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDR);
    MyI2C_ReadAck();
    MyI2C_SendByte(RegAddress);
    MyI2C_ReadAck();

    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDR | 0x01);
    MyI2C_ReadAck();
    Data = MyI2C_ReadByte();
    MyI2C_SendAck(1);
    MyI2C_Stop();

    return Data;
}

void MPU6050_Init(void)
{
    MyI2C_Init();

    // 配置电源管理和时钟源
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);

    // 配置电源管理器2
    MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);

    // 配置采样率
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);

    // 配置滤波器
    MPU6050_WriteReg(MPU6050_CONFIG, 0x06);

    // 配置陀螺仪
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);

    // 配置加速度计
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}

void MPU6050_GetData(int16_t **Accel, int16_t **Gyro)
{
    uint8_t DataH, DataL;

    DataH     = MPU6050_ReadByte(MPU6050_ACCEL_XOUT_H);
    DataL     = MPU6050_ReadByte(MPU6050_ACCEL_XOUT_L);
    *Accel[0] = (DataH << 8) | DataL;

    DataH     = MPU6050_ReadByte(MPU6050_ACCEL_YOUT_H);
    DataL     = MPU6050_ReadByte(MPU6050_ACCEL_YOUT_L);
    *Accel[1] = (DataH << 8) | DataL;

    DataH     = MPU6050_ReadByte(MPU6050_ACCEL_ZOUT_H);
    DataL     = MPU6050_ReadByte(MPU6050_ACCEL_ZOUT_L);
    *Accel[2] = (DataH << 8) | DataL;

    DataH    = MPU6050_ReadByte(MPU6050_GYRO_XOUT_H);
    DataL    = MPU6050_ReadByte(MPU6050_GYRO_XOUT_L);
    *Gyro[0] = (DataH << 8) | DataL;

    DataH    = MPU6050_ReadByte(MPU6050_GYRO_YOUT_H);
    DataL    = MPU6050_ReadByte(MPU6050_GYRO_YOUT_L);
    *Gyro[1] = (DataH << 8) | DataL;

    DataH    = MPU6050_ReadByte(MPU6050_GYRO_ZOUT_H);
    DataL    = MPU6050_ReadByte(MPU6050_GYRO_ZOUT_L);
    *Gyro[2] = (DataH << 8) | DataL;
}
