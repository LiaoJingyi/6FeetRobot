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

	//rotate 18 servos to Pos[] in t ms
	//Attention: the number labled in servo controller is exact added 1.
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
		Com.printf("T100\r\n");
		wait_ms(100);
	}
//===============================================
	//basic action for 6 feet robot
	void Stand()
	{
		//Defination of C_PWM and it won't change in the whole program, except in Drop().
		int C_PWM=1300;

		for(int i=0;i<Servo_Num/3;i++)
		{
			Pos[i*3+2]=Init_PWM;//A 1500
			Pos[i*3+1]=(Init_PWM+Up_PWM)>>1;//B 2000
			Pos[i*3]=C_PWM;//C 1300
		}
		Rotate();
	}
	//Drop down action, all servos is in initial status.
	void Drop()
	{
		for(int i=0;i<Servo_Num;i++) Pos[i]=Init_PWM;
		Rotate();
	}
	//all feet raise up
	void Reverse_stand()
	{
		int C_PWM=1300;
		for(int i=0;i<Servo_Num/3;i++)
		{
			Pos[i*3+2]=Init_PWM;//A 1500
			Pos[i*3+1]=(Init_PWM+Low_PWM)>>1;//B 1000
			Pos[i*3]=C_PWM;//C 1300
		}
		Rotate();
	}

//===============================================
	//walk action
	void Walk_towards(int N) //complete N period of walking towards, spending (N*4+2)*Standard_Rotate_Period.
	{
		Stand(); //initialization
		int B_up_PWM=2300;
		for(int i=1;i<=N;i++)
		{
			//step 2
			Pos[4]=Pos[7]=Pos[16]=B_up_PWM;//up
			Pos[2]=Pos[17]=1900; Pos[5]=Pos[14]=Init_PWM; Pos[8]=Pos[11]=1400;//pattern
			Rotate();
			//step 3
			Pos[4]=Pos[7]=Pos[16]=(Init_PWM+Up_PWM)>>1;//down
			Rotate();
			//step 4
			Pos[1]=Pos[10]=Pos[13]=B_up_PWM;//up
			Pos[2]=Pos[17]=Init_PWM; Pos[5]=Pos[14]=1100; Pos[8]=Pos[11]=1600;//pattern
			Rotate();
			//step 5
			Pos[1]=Pos[10]=Pos[13]=(Init_PWM+Up_PWM)>>1;//down
			Rotate();
		}
		Stand();
	}
	void Walk_backwards(int N) //complete N period of walking backwards, spending (N*4+2)*Standard_Rotate_Period.
	{
		Stand(); //initialization
		int B_up_PWM=2300;
		for(int i=1;i<=N;i++)
		{
			//step 7
			Pos[1]=Pos[10]=Pos[13]=B_up_PWM;//up
			Pos[2]=Pos[17]=1900; Pos[5]=Pos[14]=Init_PWM; Pos[8]=Pos[11]=1400;//pattern
			Rotate();
			//step 8
			Pos[1]=Pos[10]=Pos[13]=(Init_PWM+Up_PWM)>>1;//down
			Rotate();
			//step 9
			Pos[4]=Pos[7]=Pos[16]=B_up_PWM;//up
			Pos[2]=Pos[17]=Init_PWM; Pos[5]=Pos[14]=1100; Pos[8]=Pos[11]=1600;//pattern
			Rotate();
			//step 10 
			Pos[4]=Pos[7]=Pos[16]=(Init_PWM+Up_PWM)>>1;//down
			Rotate();
		}
		Stand();
	}
	void Anticlockwise(int N)
	{
		Stand();
		int B_up_PWM=1900;
		for(int i=1;i<=N;i++)
		{
			//step 12
			Pos[1]=Pos[10]=Pos[13]=B_up_PWM;
			Pos[2]=1900; Pos[5]=1100; Pos[8]=1400; Pos[11]=1600; Pos[14]=1500; Pos[17]=1500;
			Rotate();
			//step 13
			Pos[1]=Pos[10]=Pos[13]=(Init_PWM+Up_PWM)>>1;
			Rotate();
			//step 14
			Pos[1]=Pos[4]=Pos[7]=Pos[16]=B_up_PWM;
			Pos[2]=1400; Pos[5]=1500; Pos[8]=1600; Pos[11]=1400; Pos[14]=1100; Pos[17]=1900;
			Rotate();
			//step 15
			Pos[1]=Pos[4]=Pos[7]=Pos[16]=(Init_PWM+Up_PWM)>>1;
			Rotate();
		}
		Stand();
	}
	void Clockwise(int N)
	{
		Stand();
		int B_up_PWM=1900;
		for(int i=1;i<=N;i++)
		{
			//step 17
			Pos[4]=Pos[7]=Pos[16]=B_up_PWM;
			Pos[2]=1900; Pos[5]=1100; Pos[8]=1400; Pos[11]=1600; Pos[14]=1600; Pos[17]=1400;
			Rotate();
			//step 18
			Pos[4]=Pos[7]=Pos[16]=(Init_PWM+Up_PWM)>>1;
			Rotate();
			//step 19
			Pos[1]=Pos[10]=Pos[13]=B_up_PWM;
			Pos[2]=1400; Pos[5]=1600; Pos[8]=1600; Pos[11]=1400; Pos[14]=1100; Pos[17]=1900;
			Rotate();
			//step 20
			Pos[1]=Pos[10]=Pos[13]=(Init_PWM+Up_PWM)>>1;
			Rotate();
		}
		Stand();
	}
};
