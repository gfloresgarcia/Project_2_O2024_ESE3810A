/*
 * publisher.h
 *
 *  Created on: 3 oct. 2024
 *      Author: Gustavo Flores
 */

#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct {
	int temperature;
	int humidity;
	double latitude;
	double longitude;
} sensors;

void Task_Publisher(void *arg);
bool Publish_Location(void);

void initial_Sensors(void);

#endif /* PUBLISHER_H_ */
