#ifndef _mbed_h_
#define _mbed_h_
#include "mbed.h"
#endif // _mebed_h_

#ifndef Servo_Parameter
#define Servo_Parameter
#define Servo_Num 18
#define Low_PWM 500
#define Up_PWM 2500
#define Init_PWM 1500
#define C_PWM 1300
#endif // Servo_Parameter

struct Servo
{
    int Pos[Servo_Num];//[500,2500]
    //initialize
    Servo()
    { for(int i=0;i<Servo_Num;i++) Pos[i]=Init_PWM; }
    Servo(const int *In_Data)
    { for(int i=0;i<Servo_Num;i++) Pos[i]=*(In_Data+i); }
    //action
    void Rotate(int t)
    {
        Serial Com(p9,p10);
        for(int i=0;i<Servo_Num;i++) Com.printf("#%dP%d",i+1,Pos[i]);
        Com.printf("T%d\r\n",t);
        wait_ms(t);
    }
    void Rotate()
    {
        Serial Com(p9,p10);
        for(int i=0;i<Servo_Num;i++) Com.printf("#%dP%d",i+1,Pos[i]);
        Com.printf("T1000\r\n");
        wait_ms(1000);
    }
    void Stand()
    {
        for(int i=0;i<Servo_Num/3;i++)
        {
            Pos[i*3+2]=Init_PWM;//A
            Pos[i*3+1]=(Init_PWM+Up_PWM)>>1;//B
            Pos[i*3]=C_PWM;//C
        }
        Rotate();
    }
};