/*
 * SSD_Interface.h
 *
 *  Created on: Aug 31, 2022
 *      Author: Ahmed Youssef
 */

#ifndef HAL_SSD_SSD_INTERFACE_H_
#define HAL_SSD_SSD_INTERFACE_H_

#include "SSD_Config.h"
#include "STD.h"
#include "DIO_Interface.h"
#include <util/delay.h>

void H_SSD_Void_SSDInit(void);

void H_SSD_Void_SSDWriteNumber(u8);

#endif /* HAL_SSD_SSD_INTERFACE_H_ */
