/*
 * suscriber.c
 *
 *  Created on: 3 oct. 2024
 *      Author: Gustavo Flores
 */

#include "suscriber.h"
#include "mqtt.h"
#include "board.h"

static char topic_received[100];

/*!
 * @brief Called when subscription request finishes.
 */
void mqtt_topic_subscribed_cb(void *arg, err_t err)
{
    const char *topic = (const char *)arg;

    if (err == ERR_OK)
    {
        PRINTF("Subscribed to the topic \"%s\".\r\n", topic);
    }
    else
    {
        PRINTF("Failed to subscribe to the topic \"%s\": %d.\r\n", topic, err);
    }
}

/*!
 * @brief Called when there is a message on a subscribed topic.
 */
void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len)
{
    LWIP_UNUSED_ARG(arg);

    PRINTF("Received %u bytes from the topic \"%s\": \"", tot_len, topic);

    memset(topic_received, 0, sizeof(topic_received));
    strcpy(topic_received, topic);
}

/*!
 * @brief Called when recieved incoming published message fragment.
 */
void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags)
{
    int i;

    LWIP_UNUSED_ARG(arg);

    for (i = 0; i < len; i++)
    {
        if (isprint(data[i]))
        {
            //PRINTF("%c", (char)data[i]);

            if (strcmp(topic_received, "fire_Control_System/alarm") == 0) {
            	if ((char)data[i] == '1') setAlarm(true);
            	else setAlarm(false);
            }
            else if (strcmp(topic_received, "fire_Control_System/irrigation") == 0) {
            	if ((char)data[i] == '1') setIrrigation(true);
            	else setIrrigation(false);
            }
            else {
            	//Do nothing
            }
        }
        else
        {
            PRINTF("\\x%02x", data[i]);
        }
    }

    if (flags & MQTT_DATA_FLAG_LAST)
    {
        PRINTF("\"\r\n");
    }
}

void setAlarm(bool state) {
	if (state) {
		PRINTF("ALARMA ACTIVADA");
		LED_RED_ON();
	}
	else {
		PRINTF("ALARMA DESACTIVADA");
		LED_RED_OFF();
	}
}

void setIrrigation(bool state) {
	if (state) {
		PRINTF("RIEGO ACTIVADO");
		LED_RED_ON();
	}
	else {
		PRINTF("RIEGO DESACTIVADO");
		LED_RED_OFF();
	}
}
