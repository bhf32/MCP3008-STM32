/*
 * MCP3008.h
 *
 *  Created on: May 23, 2024
 *      Author: Ben Francis
 */

#ifndef __MCP3008_H_
#define __MCP3008_H_

#include <stdlib.h>
#include "stm32l5xx_hal.h"

/** Bit Manipulation Macros */
#define SHIFT_4    			    	   4
#define SHIFT_8     				   8
#define FIRST_10_BITS_MASK 			   0x03FF

/** Limits and Commonly used conversion Macro*/
#define MCP3008_NUM_CHANNELS       	   8
#define MCP3008_ADC_MAX				   1023
#define MCP3008_SPI_TIMEOUT			   1    //1 msec timeout

/**
 * @brief MCP3008 Driver Handle struct
 */
typedef struct
{

	GPIO_TypeDef *CS_Port;

	uint16_t CS_Pin;

    SPI_HandleTypeDef *hspi;

}MCP3008_Handle_t;

/**
 * @brief Error mapping for driver functions
 */
typedef enum
{
    MCP3008_ERROR_INVALID_ARG   	 = -1,
    MCP3008_ERROR_SPI 				 = -2

}MCP3008_STATUS;

void MCP3008_handle_init(MCP3008_Handle_t *handle, GPIO_TypeDef *cs_port, uint16_t cs_pin, SPI_HandleTypeDef *hspi);

int16_t MCP3008_read(MCP3008_Handle_t *handle, uint8_t chan);

float MCP3008_read_volts(MCP3008_Handle_t *handle, uint8_t chan, float vref);

#endif /* __MCP3008_H_ */
