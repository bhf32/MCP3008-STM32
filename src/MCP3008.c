/*
 * MCP3008.c
 *
 *  Created on: May 23, 2024
 *      Author: Ben Francis
 */

#include "MCP3008.h"

/**
 * Initialize the MCP3008 driver handle and enable the outputs
 *
 * @param handle - handle for MCP3008 driver
 * @param cs_port - CS pin GPIO port
 * @param cs_pin - CS GPIO pin number
 * @param hspi - STM32x SPI peripheral handle
 *
 * @return None
 */
void MCP3008_handle_init(MCP3008_Handle_t *handle, GPIO_TypeDef *cs_port, uint16_t cs_pin, SPI_HandleTypeDef *hspi){
	//Assign the port and pins for the SPI CS pin
	handle->CS_Port = cs_port;
	handle->CS_Pin = cs_pin;

	handle->hspi = hspi;
}

/**
 * Read the ADC input for a specified channel
 *
 * @param handle - handle for MCP3008 driver
 * @param chan - channel number to read (0 - 7)
 *
 * @return the ADC input in ADC units; MCP3008_ERROR_SPI or MCP3008_ERROR_INVALID_ARG in case of error
 */
int16_t MCP3008_read(MCP3008_Handle_t *handle, uint8_t chan){
	//Limit chan to max number of channels
	if(chan >= MCP3008_NUM_CHANNELS){
		return MCP3008_ERROR_INVALID_ARG;
	}

	//Initialize the tx and rx buffers
	uint8_t tx_data[3];
	uint8_t rx_data[3] = {0};

	tx_data[0] = 0x01; //Start bit
	tx_data[2] = 0x00;
	tx_data[1] = 0x80 | (chan << SHIFT_4);

	HAL_GPIO_WritePin(handle->CS_Port, handle->CS_Pin, GPIO_PIN_RESET);
	HAL_StatusTypeDef spi_status = HAL_SPI_TransmitReceive(handle->hspi, tx_data, rx_data, sizeof(tx_data), MCP3008_SPI_TIMEOUT);
	HAL_GPIO_WritePin(handle->CS_Port, handle->CS_Pin, GPIO_PIN_SET);

	if(spi_status != HAL_OK){
		return MCP3008_ERROR_SPI;
	}

	//Extract 10-bit ADC reading from rx buffer
	int16_t adc_reading = (int16_t)((rx_data[1] << SHIFT_8) | rx_data[2]) & FIRST_10_BITS_MASK;

	return adc_reading;
}

/**
 * Read the ADC input for a specified channel and convert to volts
 *
 * @param handle - handle for MCP3008 driver
 * @param chan - channel number to read (0 - 7)
 * @param vref - MCP3008 reference voltage (Vref)
 *
 * @return the ADC input in volts; MCP3008_ERROR_SPI or MCP3008_ERROR_INVALID_ARG in case of error
 */
float MCP3008_read_volts(MCP3008_Handle_t *handle, uint8_t chan, float vref){
	//Verify positive voltage for vref
	if(vref < 0){
		return MCP3008_ERROR_INVALID_ARG;
	}

	//Read ADC input from the channel
	int16_t adc_reading = MCP3008_read(handle, chan);

	if(adc_reading == MCP3008_ERROR_INVALID_ARG || adc_reading == MCP3008_ERROR_SPI){
		return adc_reading;
	}

	//Convert reading to volts and return value
	return ((uint16_t)adc_reading * vref)/MCP3008_ADC_MAX;
}
