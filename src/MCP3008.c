/*
 * MCP3008.c
 *
 *  Created on: May 23, 2024
 *      Author: Ben Francis
 */

#include "MCP3008.h"

uint16_t MCP3008_read(MCP3008_data_t *dev, uint16_t chan){
    /*//Deactivate communication with all ADCs
    reset_ADC_SPI();

    //Initialize arrays and variable for SPI communication
    uint8_t tx_data[3];
    uint8_t rx_data[3];
    uint16_t adc_value = 0;

    //Setup data to be transmitted to ADC devices
    tx_data[0] = 0x01;  // Start bit
    tx_data[2] = 0x00;

    uint8_t chan = 0;
    //Start with reading from ADC1
    ADC_SPI_SELECTED ADC_current_sel = ADC1_SPI_SEL;
    //Loop through all ADC channels to read and store key input
    for(uint8_t index = NUM_PIC32_ADC_CHANNELS; index < NUM_TOTAL_ADC_CHANNELS; index++){
        tx_data[1] = 0x80 | (chan << 4); //set correct bits to read from current chan
        // Activate the CS line for the correct ADC*/
        /*if(ADC_current_sel == ADC1_SPI_SEL){
            ADC1_SPI_CS_Clear();
        }
        else if(ADC_current_sel == ADC2_SPI_SEL){
            ADC2_SPI_CS_Clear();
        }
        else{
            ADC3_SPI_CS_Clear();
        }

        //Perform the SPI transaction to request the ADC value
        SPI1_WriteRead(tx_data, sizeof(tx_data), rx_data, sizeof(rx_data));

        reset_ADC_SPI();

        //Extract and process the ADC value from the received data
        adc_value = (((uint16_t)rx_data[1] << 8) | (uint16_t)rx_data[2]) & 0x03FF;
        app_keyboardData.adc_results[index] = adc_value; //store in array


        if(chan == (NUM_MCP3008_ADC_CHANNELS-1)){
            chan = 0;
            if(ADC_current_sel == ADC1_SPI_SEL){
                //Switch to second ADC when finished reading first one
                ADC_current_sel = ADC2_SPI_SEL;
            }
            else{
                //Switch to third ADC when finished reading the second one
                ADC_current_sel = ADC3_SPI_SEL;
            }
        }
        else{
            //Read from next ADC channel
            chan++;
        }
    }*/
}
