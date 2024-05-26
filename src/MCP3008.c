/*
 * MCP3008.c
 *
 *  Created on: May 23, 2024
 *      Author: Ben Francis
 */

#include "MCP3008.h"

void MCP3008_handle_init(MCP3008_Handle_t *handle, GPIO_TypeDef *cs_port, uint16_t cs_pin, SPI_HandleTypeDef *hspi){

	handle->CS_Port = cs_port;
	handle->CS_Pin = cs_pin;

	handle->hspi = hspi;

}

float MCP3008_read_volts(MCP3008_Handle_t *handle, uint16_t chan, float vref){

	if(chan >= MCP3008_NUM_CHANNELS || vref < 0){
		return MCP3008_ERROR_INVALID_ARG;
	}

	uint8_t tx_data[3];
	uint8_t rx_data[3] = {0};

	tx_data[0] = 0x01;  // Start bit
	tx_data[2] = 0x00;
	tx_data[1] = 0x80 | (chan << SHIFT_4);

	HAL_GPIO_WritePin(handle->CS_Port, handle->CS_Pin, GPIO_PIN_RESET);
	HAL_StatusTypeDef spi_status = HAL_SPI_TransmitReceive(handle->hspi, tx_data, rx_data, sizeof(tx_data), MCP3008_SPI_TIMEOUT);
	HAL_GPIO_WritePin(handle->CS_Port, handle->CS_Pin, GPIO_PIN_SET);

	if(spi_status != HAL_OK){
		return MCP3008_ERROR_SPI;
	}

	uint16_t adc_reading = (((uint16_t)rx_data[1] << SHIFT_8) | (uint16_t)rx_data[2]) & FIRST_10_BITS_MASK;

	return (adc_reading * vref)/MCP3008_ADC_MAX;
}
