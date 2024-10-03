/*
 * suscriber.h
 *
 *  Created on: 3 oct. 2024
 *      Author: Gustavo Flores
 */

#ifndef SUSCRIBER_H_
#define SUSCRIBER_H_

#include "lwip/err.h"

void mqtt_topic_subscribed_cb(void *arg, err_t err);
void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len);
void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags);

void setAlarm(bool state);
void setIrrigation(bool state);
#endif /* SUSCRIBER_H_ */
