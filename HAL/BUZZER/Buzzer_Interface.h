/*
 * Buzzer_Interface.h
 *
 *  Created on: Aug 27, 2022
 *      Author: Ahmed Youssef
 */

#ifndef HAL_BUZZER_BUZZER_INTERFACE_H_
#define HAL_BUZZER_BUZZER_INTERFACE_H_


/**************************************************_INCLUDES_*******************/
#include "Buzzer_Config.h"
#include "DIO_Interface.h"
#include <util/delay.h>
/**************************************************_PROTOTYPES_*******************/
void H_Buzzer_Void_BuzzerInit(void);
void H_Buzzer_Void_BuzzerSetOn(void);
void H_Buzzer_Void_BuzzerSetOff(void);
void H_Buzzer_Void_BuzzerOnce(void);
#endif /* HAL_BUZZER_BUZZER_INTERFACE_H_ */
