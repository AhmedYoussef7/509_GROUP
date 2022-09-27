/*
 * Servo_Prog.c
 *
 *  Created on: Sep 21, 2022
 *      Author: Ahmed Youssef
 */

#include "Servo_Interface.h"

void H_Servo_Void_ServoInit(void)
{
	M_Timer_Void_PWMInit(TIMER1_CHANNEL);
	M_Timer_Void_PWMSetFrequency(50);
}
void H_Servo_Void_ServoSetAngle(u8 Copy_U8_Angel)
{
	f32 Local_F32_Value = ((Copy_U8_Angel * 5.0 ) / 180.0) + 5.0;
	M_Timer_Void_PWMSetDutyCycle(TIMER1_CHANNEL,Local_F32_Value);
}
void H_Servo_Void_ServoSetStart(void)
{
	M_Timer_Void_PWMStart(TIMER1_CHANNEL);
}
void H_Servo_Void_ServoSetStop(void)
{
	M_Timer_Void_PWMStart(TIMER1_CHANNEL);
}

