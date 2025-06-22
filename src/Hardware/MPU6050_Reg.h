#ifndef __MPU6050_REG_H_
#define __MPU6050_REG_H_

// 定义MPU6050寄存器地址，用于配置和获取数据

// 样率分割寄存器地址，用于设置数据输出率
#define MPU6050_SMPLRT_DIV 0x19
// 配置寄存器地址，用于设置外部滤波器
#define MPU6050_CONFIG 0x1A
// 角速度计配置寄存器地址，用于设置角速度计的量程和滤波器
#define MPU6050_GYRO_CONFIG 0x1B
// 加速度计配置寄存器地址，用于设置加速度计的量程和滤波器
#define MPU6050_ACCEL_CONFIG 0x1C

// 加速度X轴输出高位寄存器地址
#define MPU6050_ACCEL_XOUT_H 0x3B
// 加速度X轴输出低位寄存器地址
#define MPU6050_ACCEL_XOUT_L 0x3C
// 加速度Y轴输出高位寄存器地址
#define MPU6050_ACCEL_YOUT_H 0x3D
// 加速度Y轴输出低位寄存器地址
#define MPU6050_ACCEL_YOUT_L 0x3E
// 加速度Z轴输出高位寄存器地址
#define MPU6050_ACCEL_ZOUT_H 0x3F
// 加速度Z轴输出低位寄存器地址
#define MPU6050_ACCEL_ZOUT_L 0x40
// 温度输出高位寄存器地址
#define MPU6050_TEMP_OUT_H 0x41
// 温度输出低位寄存器地址
#define MPU6050_TEMP_OUT_L 0x42
// 角速度X轴输出高位寄存器地址
#define MPU6050_GYRO_XOUT_H 0x43
// 角速度X轴输出低位寄存器地址
#define MPU6050_GYRO_XOUT_L 0x44
// 角速度Y轴输出高位寄存器地址
#define MPU6050_GYRO_YOUT_H 0x45
// 角速度Y轴输出低位寄存器地址
#define MPU6050_GYRO_YOUT_L 0x46
// 角速度Z轴输出高位寄存器地址
#define MPU6050_GYRO_ZOUT_H 0x47
// 角速度Z轴输出低位寄存器地址
#define MPU6050_GYRO_ZOUT_L 0x48

// 电源管理寄存器1地址，用于设置芯片的电源模式和时钟源
#define MPU6050_PWR_MGMT_1 0x6B
// 电源管理寄存器2地址，用于设置芯片的电源模式和配置
#define MPU6050_PWR_MGMT_2 0x6C
// 芯片ID寄存器地址，用于验证芯片型号
#define MPU6050_WHO_AM_I 0x75

#endif // !__MPU6050_REG_H_
