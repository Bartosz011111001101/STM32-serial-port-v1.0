/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdio.h"
#include <stdarg.h> //for va_list var arg functions
#include "math.h"
#include "gde021a1.h"
#include "stm32l0538_discovery.h"
#include "stm32l0538_discovery_epd.h"

#include "ssd1306_fonts.h"
#include "ssd1306.h"



/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

int flaga = 0;
int k = 1;
uint8_t Logo_receive[2048] = {0};
//uint8_t buffer[2048] = {0};

uint8_t Logo[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0xe0, 0xf3, 0xff, 0x3f, 0x00, 0x00,
				0x00, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
				0x00, 0x00, 0x80, 0x13, 0x04, 0x00, 0xe0, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x14, 0x04, 0x00, 0xc0, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x1c, 0x04, 0x00, 0xf0, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x08, 0x1c, 0x00, 0x70, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x08, 0xff, 0xff, 0x3f, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x08, 0xfe, 0xff, 0x1f, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x08, 0x06, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x08, 0x02, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x08, 0x02, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x70, 0x08, 0x01, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x80, 0xff, 0x0b, 0x01, 0x00, 0x00, 0x00, 0x00,
				0x00, 0xc0, 0xff, 0x1f, 0x01, 0x00, 0x00, 0x00, 0x00,
				0x00, 0xe0, 0x7f, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00,
				0x00, 0xf0, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x70, 0x00, 0x80, 0x1f, 0x00, 0x00, 0x00, 0x00,
				0xf8, 0x38, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00,
				0x84, 0x39, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00,
				0x04, 0x3d, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00,
				0x24, 0x3f, 0x00, 0x1c, 0x38, 0x00, 0x00, 0x00, 0x00,
				0x64, 0x3e, 0x88, 0x65, 0x38, 0x00, 0x00, 0x00, 0x00,
				0xc8, 0x1e, 0xf0, 0x87, 0x30, 0x80, 0x07, 0x00, 0x00,
				0x88, 0x1f, 0x00, 0x0f, 0x70, 0x00, 0x0c, 0x00, 0x00,
				0x18, 0x0e, 0x01, 0x0c, 0x60, 0x00, 0x07, 0x00, 0x00,
				0xf0, 0x0e, 0x03, 0x00, 0x60, 0xc0, 0x3f, 0x00, 0x00,
				0x80, 0x07, 0x1f, 0x00, 0x60, 0x00, 0xfc, 0x01, 0x00,
				0x00, 0x07, 0x1c, 0x00, 0x60, 0xf8, 0xf8, 0x03, 0x00,
				0x00, 0x87, 0xe0, 0x01, 0x60, 0x07, 0x8f, 0x1f, 0x00,
				0x00, 0x83, 0xe0, 0x03, 0xc0, 0x00, 0x98, 0x0f, 0x00,
				0x80, 0xc3, 0xe0, 0x07, 0x40, 0x00, 0x60, 0x05, 0x00,
				0x80, 0x43, 0xe0, 0x0f, 0x60, 0x00, 0x80, 0x3f, 0x00,
				0x80, 0x41, 0xe0, 0x7f, 0x60, 0x00, 0xf8, 0x0f, 0x00,
				0x80, 0x41, 0xe0, 0xff, 0x63, 0xba, 0x07, 0x3d, 0x00,
				0x80, 0x41, 0xe0, 0xff, 0x7f, 0x86, 0x84, 0x3f, 0x00,
				0xc0, 0x41, 0xe1, 0xff, 0x7f, 0x86, 0x87, 0x1f, 0x00,
				0xc0, 0x41, 0xe1, 0xff, 0x3f, 0x04, 0x80, 0x3f, 0x00,
				0xc0, 0x41, 0xe1, 0xff, 0x3f, 0x08, 0x80, 0x39, 0x00,
				0xc0, 0x41, 0xe2, 0xff, 0x2f, 0xd0, 0x83, 0x1d, 0x00,
				0xc0, 0x41, 0xe2, 0xff, 0x23, 0x10, 0x8e, 0x7f, 0x00,
				0xc0, 0x81, 0xe7, 0x7f, 0x30, 0x30, 0x8a, 0x7f, 0x00,
				0xc0, 0x81, 0xc5, 0x0f, 0x70, 0x60, 0xce, 0x3f, 0x00,
				0xc0, 0x81, 0xc4, 0x07, 0x50, 0x20, 0xe0, 0x39, 0x00,
				0xc0, 0x81, 0x88, 0x01, 0xf0, 0x10, 0xe0, 0x1f, 0x00,
				0xc0, 0x81, 0x08, 0x00, 0xf8, 0x30, 0xb0, 0x0d, 0x00,
				0xc0, 0x81, 0x08, 0x00, 0xb8, 0xc1, 0x97, 0x03, 0x00,
				0xc0, 0xc1, 0x08, 0x00, 0x38, 0xe1, 0x58, 0x01, 0x00,
				0xc0, 0x41, 0x08, 0x40, 0x38, 0x06, 0xee, 0x01, 0x00,
				0xc0, 0x61, 0xc8, 0x03, 0x18, 0xfc, 0xff, 0x00, 0x00,
				0xc0, 0xe1, 0x40, 0x06, 0x1c, 0xc0, 0x71, 0x00, 0x00,
				0xc0, 0x81, 0x40, 0x04, 0x1c, 0x00, 0x1f, 0x00, 0x00,
				0xe0, 0xc1, 0x40, 0x14, 0x1c, 0x80, 0x01, 0x00, 0x00,
				0xe0, 0x40, 0xc0, 0x17, 0x0e, 0x00, 0x00, 0x00, 0x00,
				0xc0, 0x40, 0x02, 0x17, 0x06, 0x00, 0x00, 0x00, 0x00,
				0xf0, 0x00, 0x02, 0x10, 0x06, 0x00, 0x00, 0x00, 0x00,
				0x18, 0x01, 0x1c, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00,
				0xfc, 0x01, 0x70, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00,
				0x14, 0x02, 0xc0, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00,
				0x14, 0x02, 0x80, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00,
				0x04, 0x0f, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00,
				0xf4, 0x1d, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00,
				0x1c, 0x78, 0x00, 0x60, 0x07, 0x00, 0x00, 0x00, 0x00,
				0x00, 0xf0, 0xc1, 0x9a, 0x07, 0x00, 0x00, 0x00, 0x00,
				0x00, 0xf0, 0xf3, 0x87, 0x07, 0x00, 0x00, 0x00, 0x00,
				0x00, 0xc0, 0xff, 0x07, 0x0f, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x80, 0xbf, 0x07, 0x0e, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x80, 0x7f, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x0c, 0x8c, 0x07, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x7c, 0xcc, 0x0c, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0xf8, 0x78, 0x08, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0xf0, 0x08, 0x08, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0xe0, 0x08, 0x0a, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0xf0, 0x67, 0x0e, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x10, 0xac, 0x0f, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0xf0, 0x3c, 0x03, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0x03, 0x00, 0x00,
				0x18, 0x00, 0x00, 0x8c, 0xff, 0xff, 0x03, 0x00, 0x00,
				0xec, 0x07, 0x00, 0x0c, 0x00, 0x00, 0x03, 0x00, 0x00,
				0x04, 0x78, 0x00, 0x0c, 0x00, 0x00, 0x03, 0x00, 0x00,
				0x04, 0x80, 0xff, 0x0f, 0x00, 0x00, 0x03, 0x00, 0x00,
				0x04, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x03, 0x00, 0x00,
				0x04, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x03, 0x00, 0x00,
				0x04, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x03, 0x00, 0x00,
				0x04, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x03, 0x00, 0x00,
				0x0c, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x03, 0x00, 0x00,
				0x78, 0xf0, 0xff, 0x1f, 0x00, 0x00, 0x03, 0x00, 0x00,
				0xc0, 0x1f, 0x00, 0x1c, 0x00, 0x00, 0x03, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x07, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x07, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x07, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x0f, 0x00, 0x00,
				0x00, 0x00, 0xfc, 0x0f, 0x00, 0x00, 0x0e, 0x00, 0x00,
				0x00, 0xe0, 0x03, 0x0c, 0x00, 0x00, 0x0e, 0x00, 0x00,
				0x00, 0x1e, 0x00, 0x0c, 0x00, 0x00, 0x0e, 0x00, 0x00,
				0xc0, 0x01, 0x00, 0x0c, 0x00, 0x00, 0x06, 0x00, 0x00,
				0x60, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x06, 0x00, 0x00,
				0x10, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x06, 0x00, 0x00,
				0x10, 0x80, 0xff, 0x0f, 0x00, 0x00, 0x06, 0x00, 0x00,
				0x08, 0x70, 0x00, 0x0c, 0x00, 0x00, 0x06, 0x00, 0x00,
				0xf8, 0x0f, 0x00, 0x0c, 0x00, 0x00, 0x06, 0x00, 0x00,
				0x14, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x06, 0x00, 0x00,
				0x14, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x06, 0x00, 0x00,
				0x1c, 0x00, 0xe0, 0x0f, 0x00, 0x00, 0x06, 0x00, 0x00,
				0x18, 0x00, 0x1e, 0x0c, 0x00, 0x00, 0x06, 0x00, 0x00,
				0x10, 0xe0, 0x01, 0x0e, 0x00, 0x00, 0x06, 0x00, 0x00,
				0x10, 0x18, 0xf8, 0x0d, 0x00, 0x00, 0x06, 0x00, 0x00,
				0xf0, 0xcf, 0x07, 0x0e, 0x00, 0x00, 0x06, 0x00, 0x00,
				0x30, 0x3c, 0xf0, 0x0d, 0x00, 0x00, 0x06, 0x00, 0x00,
				0x10, 0x06, 0x1e, 0x0e, 0x00, 0x00, 0x07, 0x00, 0x00,
				0xb0, 0x81, 0x03, 0x0e, 0x00, 0x80, 0x07, 0x00, 0x00,
				0xe0, 0x60, 0x00, 0x0c, 0x00, 0xc0, 0x07, 0x00, 0x00,
				0x00, 0x18, 0x00, 0x1c, 0x00, 0xe0, 0x04, 0x00, 0x00,
				0x00, 0x06, 0x00, 0x1c, 0x00, 0x60, 0x04, 0x00, 0x00,
				0x00, 0x03, 0x00, 0x1c, 0x00, 0xc0, 0x00, 0x00, 0x00,
				0x80, 0x00, 0x00, 0x1c, 0x00, 0x80, 0x03, 0x00, 0x00,
				0x40, 0x00, 0x00, 0x1f, 0x00, 0x80, 0x03, 0x00, 0x00,
				0x20, 0x00, 0x80, 0x1c, 0x00, 0x00, 0x06, 0x00, 0x00,
				0x20, 0x00, 0x7c, 0x0c, 0x00, 0x00, 0x0e, 0x00, 0x00,
				0x20, 0x00, 0x03, 0x0c, 0x00, 0x00, 0x0c, 0x00, 0x00,
				0x30, 0xe0, 0x00, 0x0c, 0x00, 0x00, 0x38, 0x00, 0x00,
				0x10, 0x3c, 0x00, 0x0c, 0x00, 0x00, 0x38, 0x00, 0x00,
				0x90, 0x07, 0x00, 0x0c, 0x1c, 0x00, 0x30, 0x00, 0x00,
				0xd0, 0x00, 0x00, 0x0c, 0xff, 0x7f, 0x70, 0x00, 0x00,
				0x50, 0x00, 0x00, 0xcc, 0xff, 0x7f, 0xc0, 0x01, 0x00,
				0x50, 0x00, 0x00, 0xfc, 0x00, 0xe0, 0x80, 0x0f, 0x00,
				0x50, 0x00, 0x00, 0x3c, 0x00, 0xe0, 0x00, 0x3c, 0x00,
				0x70, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0xe8, 0x01,
				0x60, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x10, 0x07,
				0x40, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0xe0, 0x04,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x05,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x81, 0x07, 0x05,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x81, 0x8f, 0x05,
				0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x80, 0xc8, 0x04,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x6f, 0x04,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x20, 0x04,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x30, 0x04,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x78, 0x06,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0xcc, 0x02,
				0x00, 0x00, 0x00, 0x00, 0xc0, 0x02, 0x00, 0x0e, 0x03,
				0x00, 0x00, 0x00, 0x00, 0xc0, 0x01, 0x00, 0x07, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x07, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0x80, 0x03, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xdf, 0x03, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0xcc, 0xff, 0x01, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xe0, 0x01, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0xf0, 0x01, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xba, 0x01, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x39, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

};

uint8_t buffer[sizeof(Logo)]; // obszar pamieci o ulotnej zawartosci
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void clear_ssd1306();
void refreash_display();

void sendHexData(uint8_t *data, size_t size, UART_HandleTypeDef *huart) {
    char hexStr[sizeof(Logo)];
    for (int i = 0; i < size; i++) {
        snprintf(hexStr, sizeof(hexStr), "%2X", data[i]);
        HAL_UART_Transmit(huart, (uint8_t *)hexStr, 2, HAL_MAX_DELAY);
        HAL_UART_Transmit(huart, (uint8_t *)" ", 1, HAL_MAX_DELAY);
        if (k == 9)
                 {
                     printf("\r\n");
                     k = 0;
                 }
                 k++;
    }
}
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
void myprintf(const char *fmt, ...);
int _write(int file, char *ptr, int len);
void USART2_Init(void);
void USART2_SendChar(char c);
char USART2_ReceiveChar(void);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_SPI1_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/*
void myprintf(const char *fmt, ...)
{
  static char buffer2[256];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer2, sizeof(buffer2), fmt, args);
  va_end(args);

  int len = strlen(buffer2);
  HAL_UART_Transmit(&huart1, (uint8_t*)buffer2, len, -1);

}
*/
void refreash_display(char tekst[])
{
	clear_ssd1306();
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString (tekst, Font_11x18, 1);
	HAL_Delay(10);
	ssd1306_UpdateScreen(); // Display
}


void clear_ssd1306()
{
	ssd1306_Fill(0);  // Wypełnij ekran czarnym kolorem
	ssd1306_UpdateScreen();
}

int _write(int file, char *ptr, int len)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)ptr, len, HAL_MAX_DELAY);
    return len;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  ssd1306_Init();
  HAL_Delay(100);
  ssd1306_SetCursor(0,0);
  HAL_UART_Receive_IT(&huart1, buffer, sizeof(buffer));
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    if (HAL_GPIO_ReadPin(BSP_GPIO_Port, BSP_Pin) == GPIO_PIN_RESET)
       {
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		refreash_display("Default");
		BSP_EPD_Init();
		uint8_t a = 0;
		uint8_t b = 0;
		uint8_t c = 72;
		uint8_t d = 172;
		BSP_EPD_Clear(EPD_COLOR_WHITE);
		gde021a1_DrawImage(a, b, c, d, Logo);
		gde021a1_RefreshDisplay();
		HAL_Delay(1000);
       }

    else if (HAL_GPIO_ReadPin(Send_GPIO_Port, Send_Pin) == GPIO_PIN_RESET)
       {
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
        HAL_Delay(50);
 	    printf("Image raw data...\r\n");
 	 	sendHexData(Logo, sizeof(Logo), &huart1);  // Wysyłamy pierwsze 16 bajtów w formacie hex
 	 	char newline[] = "\r\n";
 	 	HAL_UART_Transmit(&huart1, (uint8_t *)newline, sizeof(newline) - 1, HAL_MAX_DELAY);
 	 	printf("\r\nData have sent\r\n");
 	 	refreash_display("Sent data");
 	 	HAL_Delay(1000);
       }
	 else if (HAL_GPIO_ReadPin(SSD1306_GPIO_Port, SSD1306_Pin) == GPIO_PIN_RESET)
	   {
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		clear_ssd1306();
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString ("", Font_11x18, 1);
		HAL_Delay(10);
		ssd1306_UpdateScreen(); // Display
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		HAL_Delay(1000);
	   }
	  else if (flaga == 1)
	  {
		flaga = 0;
        refreash_display("Received");
		HAL_Delay(50);
        HAL_Delay(3000);
		BSP_EPD_Init();
		uint8_t a = 0;
		uint8_t b = 0;
		uint8_t c = 72;
		uint8_t d = 172;
		BSP_EPD_Clear(EPD_COLOR_WHITE);
		gde021a1_DrawImage(a, b, c, d, buffer);
		gde021a1_RefreshDisplay();
	  }
	  else
	  {
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_SYSCLK;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00300F38;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : Send_Pin */
  GPIO_InitStruct.Pin = Send_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Send_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SSD1306_Pin BSP_Pin */
  GPIO_InitStruct.Pin = SSD1306_Pin|BSP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
		{
		 HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
         HAL_UART_Receive_IT(&huart1, buffer, sizeof(buffer));
         flaga = 1;
		}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
