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

uint16_t MCP3008_read(MCP3008_data_t *dev, uint16_t chan);

#endif /* __MCP3008_H_ */
