/*
 * publisher.c
 *
 *  Created on: 3 oct. 2024
 *      Author: Gustavo Flores
 */

#include "publisher.h"
#include "lwip/tcpip.h"
#include "mqtt.h"

extern mqtt_client_t *mqtt_client;
extern volatile bool connected;
sensors testSensors;

void initial_Sensors(void) {
	testSensors.temperature = 17;
	testSensors.humidity = 36;
	testSensors.latitude = 12.4672;
	testSensors.longitude = 18.6823;
}

// Called when publish request finishes
static void mqtt_message_published_cb(void *arg, err_t err)
{
    const char *topic = (const char *)arg;

    if (err == ERR_OK)
    {
        PRINTF("Published to the topic \"%s\".\r\n", topic);
    }
    else
    {
        PRINTF("Failed to publish to the topic \"%s\": %d.\r\n", topic, err);
    }
}

//Publishes a message. To be called on Task_Publisher
static void publish_variable(void *ctx)
{
    static const char *topic_temperature = "fire_Control_System/temperature";
    char message_temperature[100] = {0};
    int length_temperature = sprintf(message_temperature, "{'temperature':%d}", testSensors.temperature);

    static const char *topic_humidity = "fire_Control_System/humidity";
    char message_humidity[100] = {0};
    int length_humidity = sprintf(message_humidity, "{'humidity':%d}", testSensors.humidity);


    LWIP_UNUSED_ARG(ctx);

    mqtt_publish(mqtt_client, topic_temperature, message_temperature, strlen(message_temperature), 1, 0, mqtt_message_published_cb, (void *)topic_temperature);
    mqtt_publish(mqtt_client, topic_humidity, message_humidity, strlen(message_humidity), 1, 0, mqtt_message_published_cb, (void *)topic_humidity);
}

//Function to publish location GPS with retain true
static void publish_location(void *ctx)
{
    static const char *topic_location = "fire_Control_System/location";

    int latitudePartInt = (int)testSensors.latitude;
    int latitudePartDecimal = (int)((testSensors.latitude - latitudePartInt) * 1000);

    int longitudePartInt = (int)testSensors.longitude;
    int longitudePartDecimal = (int)((testSensors.longitude - longitudePartInt) * 1000);

    char message[100] = {0};
    int length = sprintf(message, "{'location':'Latitude: %d.%03d, Longitude: %d.%03d'}", latitudePartInt, latitudePartDecimal, longitudePartInt, longitudePartDecimal);

    LWIP_UNUSED_ARG(ctx);

    mqtt_publish(mqtt_client, topic_location, message, length, 1, 1, mqtt_message_published_cb, (void *)topic_location);
}

void Task_Publisher(void *arg) {
	err_t err;

	for (;;) {

		if (connected) {
			err = tcpip_callback(publish_variable, NULL);
		}

		sys_msleep(10000U);
	}
}

bool Publish_Location(void) {
	err_t err;

	if (connected) {
		err = tcpip_callback(publish_location, NULL);
	}

	if (err == ERR_OK) return true;
	else return false;
}
