/*
 * LCD_Prog.c
 *
 *  Created on: Sep 4, 2022
 *      Author: Ahmed Youssef
 */


#include "LCD_Interface.h"
#include "LCD_Private.h"


void H_LCD_Void_LCDInit(void)
{
#if   LCD_MODE   ==   _8_BIT_MODE
	M_DIO_Void_SetPinDirection(LCD_D0_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D1_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D2_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D3_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D4_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D5_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D6_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D7_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_RS_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_EN_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_RW_PIN,OUTPUT);
	M_DIO_Void_SetPinValue(LCD_RW_PIN,LOW);
	H_LCD_Void_LCDWriteCommand(LCD_8_BIT_MODE);
	H_LCD_Void_LCDWriteCommand(LCD_DISPLAY_ON_CURSOR_OFF);
#elif LCD_MODE   ==   _4_BIT_MODE
	M_DIO_Void_SetPinDirection(LCD_D4_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D5_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D6_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_D7_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_RS_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_EN_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(LCD_RW_PIN,OUTPUT);
	M_DIO_Void_SetPinValue(LCD_RW_PIN,LOW);

	H_LCD_Void_LCDWriteCommand(LCD_4_BIT_MODE_1);
	H_LCD_Void_LCDWriteCommand(LCD_4_BIT_MODE_2);
	H_LCD_Void_LCDWriteCommand(LCD_4_BIT_MODE_3);

	H_LCD_Void_LCDWriteCommand(LCD_DISPLAY_ON_CURSOR_OFF);
	H_LCD_Void_LCDWriteCommand(LCD_CLEAR);
	H_LCD_Void_LCDWriteCommand(LCD_RETURN_HOME);
#endif
}

void H_LCD_Void_LCDWriteCharacter(u8 Copy_U8_Character)
{
	M_DIO_Void_SetPinValue(LCD_RS_PIN,HIGH);
#if   LCD_MODE   ==   _8_BIT_MODE
	H_LCD_Void_SetLCDPins(Copy_U8_Character);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,LOW);
#elif LCD_MODE   ==   _4_BIT_MODE
	H_LCD_Void_SetLCDPins(Copy_U8_Character >> 4);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,LOW);
	_delay_ms(1);
	H_LCD_Void_SetLCDPins(Copy_U8_Character);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,LOW);
#endif
	_delay_ms(1);
}

void H_LCD_Void_LCDWriteCommand(u8 Copy_U8_Command)
{
	M_DIO_Void_SetPinValue(LCD_RS_PIN,LOW);
#if   LCD_MODE   ==   _8_BIT_MODE
	H_LCD_Void_SetLCDPins(Copy_U8_Command);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,LOW);
#elif LCD_MODE   ==   _4_BIT_MODE
	H_LCD_Void_SetLCDPins(Copy_U8_Command >> 4);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,LOW);
	_delay_ms(1);
	H_LCD_Void_SetLCDPins(Copy_U8_Command);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,HIGH);
	_delay_ms(1);
	M_DIO_Void_SetPinValue(LCD_EN_PIN,LOW);
#endif
	_delay_ms(1);
}

void H_LCD_Void_LCDWriteString(u8* Copy_U8_P)
{
	u8 Local_U8_Counter = 0;
	while(Copy_U8_P[Local_U8_Counter] != '\0')
	{
		H_LCD_Void_LCDWriteCharacter(Copy_U8_P[Local_U8_Counter]);
		Local_U8_Counter++;
	}
}

void H_LCD_Void_LCDWriteNumber(f32 Local_f32_Number)
{
	if(Local_f32_Number == 0)
	{
		H_LCD_Void_LCDWriteCharacter('0');
	}

	if(Local_f32_Number < 0)
	{
		H_LCD_Void_LCDWriteCharacter('-');
		Local_f32_Number =Local_f32_Number * -1;
	}

	if(Local_f32_Number > 0)
	{
		u8 Local_u8_Arr[10]={0};	// Unsigned integer max digit is 10;
		s8 Local_s8_Counter=0;
		u32 Local_u32_IntNumber = Local_f32_Number ;
		u8 Local_u8_Decimal_Pos = -1;
		while((Local_f32_Number - Local_u32_IntNumber) > 0)
		{
			Local_f32_Number *= 10.0;
			Local_u32_IntNumber=Local_f32_Number;
			Local_u8_Decimal_Pos++;
		}
		while(Local_u32_IntNumber != 0){
			Local_u8_Arr[Local_s8_Counter] = (Local_u32_IntNumber%10);
			Local_s8_Counter++;
			Local_u32_IntNumber = Local_u32_IntNumber / 10;
		}
		Local_s8_Counter--;
		while(Local_s8_Counter>-1)
		{
			if((Local_u8_Decimal_Pos !=-1) && (Local_s8_Counter == Local_u8_Decimal_Pos))
			{
				H_LCD_Void_LCDWriteCharacter('.');
			}
			H_LCD_Void_LCDWriteCharacter(Local_u8_Arr[Local_s8_Counter]+48);	// Ascii =Num + 48
			Local_s8_Counter--;
		}
	}

}


void H_LCD_Void_LCDGoTo(u8 Copy_U8_Row,u8 Copy_U8_Col)
{
	u8 Local_U8Arr [2] = {0x80 , 0xC0};
	H_LCD_Void_LCDWriteCommand(Local_U8Arr[Copy_U8_Row] + Copy_U8_Col);
}

void H_LCD_Void_LCDClear(void)
{
	H_LCD_Void_LCDWriteCommand(LCD_CLEAR);
}

static void H_LCD_Void_SetLCDPins(u8 Copy_U8_Pins)
{
#if   LCD_MODE   ==   _8_BIT_MODE
	M_DIO_Void_SetPinValue(LCD_D0_PIN,Copy_U8_Pins >> 0 & 0x01);
	M_DIO_Void_SetPinValue(LCD_D1_PIN,Copy_U8_Pins >> 1 & 0x01);
	M_DIO_Void_SetPinValue(LCD_D2_PIN,Copy_U8_Pins >> 2 & 0x01);
	M_DIO_Void_SetPinValue(LCD_D3_PIN,Copy_U8_Pins >> 3 & 0x01);
	M_DIO_Void_SetPinValue(LCD_D4_PIN,Copy_U8_Pins >> 4 & 0x01);
	M_DIO_Void_SetPinValue(LCD_D5_PIN,Copy_U8_Pins >> 5 & 0x01);
	M_DIO_Void_SetPinValue(LCD_D6_PIN,Copy_U8_Pins >> 6 & 0x01);
	M_DIO_Void_SetPinValue(LCD_D7_PIN,Copy_U8_Pins >> 7 & 0x01);
#elif LCD_MODE   ==   _4_BIT_MODE
	M_DIO_Void_SetPinValue(LCD_D4_PIN,Copy_U8_Pins >> 0 & 0x01);
	M_DIO_Void_SetPinValue(LCD_D5_PIN,Copy_U8_Pins >> 1 & 0x01);
	M_DIO_Void_SetPinValue(LCD_D6_PIN,Copy_U8_Pins >> 2 & 0x01);
	M_DIO_Void_SetPinValue(LCD_D7_PIN,Copy_U8_Pins >> 3 & 0x01);
#endif
}



