#include "stm32f10x.h"
#include "Serial.h"
#include "atoi.h"
#include "PWM.h"

extern boolean RECEIVE_SIGN;
extern struct ReceiveBuffer Buffer;

int main()
{
    Serial_Init();
    PWM_Init();
    PWM_SetCompare2(0);
    int PWM_Number = 0;

    while (1) {
        if (RECEIVE_SIGN) {
            PWM_Number = atoi(Buffer.RxBuffer, Buffer.RxIndex);
            PWM_SetCompare2(PWM_Number);
            Serial_SPrintf("占空比已更改为: %.1lf%%", PWM_Number / 19999.0 * 100);
            RECEIVE_SIGN = false;
            ResetRxData();
        }
    }
}
