/*
 * DCMotor_Private.h
 *
 *  Created on: Sep 21, 2022
 *      Author: Ahmed Youssef
 */

#ifndef HAL_DCMOTOR_DCMOTOR_PRIVATE_H_
#define HAL_DCMOTOR_DCMOTOR_PRIVATE_H_

#include "DCMotor_Interface.h"

void H_DCMotor_Void_DCMotorInit(void)
{
	M_DIO_Void_SetPinDirection(DC_MOTOR_PIN1,OUTPUT);
	M_DIO_Void_SetPinDirection(DC_MOTOR_PIN2,OUTPUT);
	M_Timer_Void_PWMInit(TIMER1_CHANNEL);
}
void H_DCMotor_Void_DCMotorSetSpeed(u32 Copy_U32_MotorSpeed)
{
	M_Timer_Void_PWMSetDutyCycle(TIMER1_CHANNEL,Copy_U32_MotorSpeed);
}
void H_DCMotor_Void_DCMotorSetDirection(u8 Copy_U8_Direction)
{
switch(Copy_U8_Direction)
{
case ACW:
	M_DIO_Void_SetPinValue(DC_MOTOR_PIN1,LOW);
	M_DIO_Void_SetPinValue(DC_MOTOR_PIN2,HIGH);
	break;
case CW:
	M_DIO_Void_SetPinValue(DC_MOTOR_PIN1,HIGH);
	M_DIO_Void_SetPinValue(DC_MOTOR_PIN2,LOW);
	break;
}
}
void H_DCMotor_Void_DCMotorStart(void)
{
	M_Timer_Void_PWMStart(TIMER1_CHANNEL);

}
void H_DCMotor_Void_DCMotorStop(void)
{
	M_Timer_Void_PWMStop(TIMER1_CHANNEL);
}


#endif /* HAL_DCMOTOR_DCMOTOR_PRIVATE_H_ */
