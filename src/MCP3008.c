/*
 * MCP3008.c
 *
 *  Created on: May 23, 2024
 *      Author: Ben Francis
 */

#include "MCP3008.h"

MCP3008_STATUS MCP3008_handle_init(MCP3008_data_t *handle, GPIO_TypeDef *CS_Port, uint16_t CS_Pin, SPI_HandleTypeDef *hspi){

	handle->CS_Port = CS_Port;
	handle->CS_Pin = CS_Pin;

	handle->hspi = hspi;

}

uint16_t MCP3008_read(MCP3008_data_t *handle, uint16_t chan){

}
