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
	bool isTherePeople;
} sensors;

void Task_Publisher(void *arg);
bool Publish_Location(void);

void evaluate_variables(int temperature, int humidity, bool people);

void initial_Sensors(void);

#endif /* PUBLISHER_H_ */
