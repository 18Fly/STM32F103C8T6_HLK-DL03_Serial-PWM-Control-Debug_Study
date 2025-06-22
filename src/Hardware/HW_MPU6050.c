#include "HW_MPU6050.h"

#define HW_MPU6050_ADDR 0xD0

void MPU6050_WaitEvent(I2C_TypeDef *I2Cx, uint32_t I2C_EVENT)
{
    uint32_t TimeCount = 0;
    while (TimeCount++ < 10000 && I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS);
}

void HW_MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
    // MyI2C_Start();
    // MyI2C_SendByte(HW_MPU6050_ADDR);
    // MyI2C_ReadAck();
    // MyI2C_SendByte(RegAddress);
    // MyI2C_ReadAck();
    // MyI2C_SendByte(Data);
    // MyI2C_ReadAck();
    // MyI2C_Stop();

    I2C_GenerateSTART(I2C2, ENABLE);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(I2C2, HW_MPU6050_ADDR, I2C_Direction_Transmitter);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

    I2C_SendData(I2C2, RegAddress);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING);

    I2C_SendData(I2C2, Data);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);

    I2C_GenerateSTOP(I2C2, ENABLE);
}

uint8_t HW_MPU6050_ReadByte(uint8_t RegAddress)
{
    uint8_t Data;
    // MyI2C_Start();
    // MyI2C_SendByte(HW_MPU6050_ADDR);
    // MyI2C_ReadAck();
    // MyI2C_SendByte(RegAddress);
    // MyI2C_ReadAck();

    // MyI2C_Start();
    // MyI2C_SendByte(HW_MPU6050_ADDR | 0x01);
    // MyI2C_ReadAck();
    // Data = MyI2C_ReadByte();
    // MyI2C_SendAck(1);
    // MyI2C_Stop();

    I2C_GenerateSTART(I2C2, ENABLE);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(I2C2, HW_MPU6050_ADDR, I2C_Direction_Transmitter);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

    I2C_SendData(I2C2, RegAddress);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);

    I2C_GenerateSTART(I2C2, ENABLE);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(I2C2, HW_MPU6050_ADDR, I2C_Direction_Receiver);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);

    I2C_AcknowledgeConfig(I2C2, DISABLE);
    I2C_GenerateSTOP(I2C2, ENABLE);

    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED);

    Data = I2C_ReceiveData(I2C2);

    I2C_AcknowledgeConfig(I2C2, ENABLE);

    return Data;
}

void HW_MPU6050_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    I2C_InitTypeDef I2C_InitStructure;
    // 时钟速度
    I2C_InitStructure.I2C_ClockSpeed = 50000;
    // 占空比（用于快速模式下）
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    // 模式选择
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    // 作为从机设定自身地址
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;
    // 响应应答使能
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    // 可应答地址设置
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C2, &I2C_InitStructure);

    I2C_Cmd(I2C2, ENABLE);

    // 配置电源管理和时钟源
    HW_MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);

    // 配置电源管理器2
    HW_MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);

    // 配置采样率
    HW_MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);

    // 配置滤波器
    HW_MPU6050_WriteReg(MPU6050_CONFIG, 0x06);

    // 配置陀螺仪
    HW_MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);

    // 配置加速度计
    HW_MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}

void HW_MPU6050_GetData(int16_t **Accel, int16_t **Gyro)
{
    uint8_t DataH, DataL;

    DataH     = HW_MPU6050_ReadByte(MPU6050_ACCEL_XOUT_H);
    DataL     = HW_MPU6050_ReadByte(MPU6050_ACCEL_XOUT_L);
    *Accel[0] = (DataH << 8) | DataL;

    DataH     = HW_MPU6050_ReadByte(MPU6050_ACCEL_YOUT_H);
    DataL     = HW_MPU6050_ReadByte(MPU6050_ACCEL_YOUT_L);
    *Accel[1] = (DataH << 8) | DataL;

    DataH     = HW_MPU6050_ReadByte(MPU6050_ACCEL_ZOUT_H);
    DataL     = HW_MPU6050_ReadByte(MPU6050_ACCEL_ZOUT_L);
    *Accel[2] = (DataH << 8) | DataL;

    DataH    = HW_MPU6050_ReadByte(MPU6050_GYRO_XOUT_H);
    DataL    = HW_MPU6050_ReadByte(MPU6050_GYRO_XOUT_L);
    *Gyro[0] = (DataH << 8) | DataL;

    DataH    = HW_MPU6050_ReadByte(MPU6050_GYRO_YOUT_H);
    DataL    = HW_MPU6050_ReadByte(MPU6050_GYRO_YOUT_L);
    *Gyro[1] = (DataH << 8) | DataL;

    DataH    = HW_MPU6050_ReadByte(MPU6050_GYRO_ZOUT_H);
    DataL    = HW_MPU6050_ReadByte(MPU6050_GYRO_ZOUT_L);
    *Gyro[2] = (DataH << 8) | DataL;
}
