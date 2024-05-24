/*
 * MCP3008.h
 *
 *  Created on: May 23, 2024
 *      Author: Ben Francis
 */

#ifndef __MCP3008_H_
#define __MCP3008_H_

#include <stdlib.h>
#include "main.h"

typedef struct
{

	GPIO_TypeDef *CS_Port;

	uint16_t CS_Pin;

    SPI_HandleTypeDef *hspi;

}MCP3008_Handle_t;

typedef enum
{
	MCP3008_OK 						 = 0,
	MCP3008_ERROR					 = 1

}MCP3008_STATUS;

MCP3008_STATUS MCP3008_handle_init(MCP3008_data_t *handle, GPIO_TypeDef *CS_Port, uint16_t CS_Pin, SPI_HandleTypeDef *hspi);

uint16_t MCP3008_read(MCP3008_data_t *handle, uint16_t chan);

#endif /* __MCP3008_H_ */
