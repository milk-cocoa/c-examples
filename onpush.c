#include "MQTTClient.h"
#include "MQTTClientPersistence.h"

#include <stdio.h>
#include <signal.h>
#include <memory.h>
#include "app.h"


#if defined(WIN32)
#include <Windows.h>
#define sleep Sleep
#else
#include <sys/time.h>
#include <stdlib.h>
#endif


volatile int toStop = 0;


void myconnect(MQTTClient* client, MQTTClient_connectOptions* opts)
{
	int rc = 0;
	if ((rc = MQTTClient_connect(*client, opts)) != 0)
	{
		printf("Failed to connect, return code %d\n", rc);
		exit(-1);	
	}
}


void cfinish(int sig)
{
	signal(SIGINT, NULL);
	toStop = 1;
}


struct opts_struct
{
	char* clientid;
	int nodelimiter;
	char* delimiter;
	int qos;
	char* token;
	char* appid;
	char* host;
	char* port;
  int showtopics;
} opts =
{
	"stdout-subscriber", 0, "\n", 0, TOKEN, APPID, HOST, PORT, 0
};


int main(int argc, char** argv)
{
	MQTTClient client;
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	char* topic = NULL;
	int rc = 0;
	char url[100];

	topic = TOPIC;

  if (strchr(topic, '#') || strchr(topic, '+'))
		opts.showtopics = 1;
  if (opts.showtopics)
		printf("topic is %s\n", topic);

	sprintf(url, "%s:%s", opts.host, opts.port);

	rc = MQTTClient_create(&client, url, opts.clientid, MQTTCLIENT_PERSISTENCE_NONE, NULL);

	signal(SIGINT, cfinish);
	signal(SIGTERM, cfinish);

	conn_opts.keepAliveInterval = 10;
	conn_opts.reliable = 0;
	conn_opts.cleansession = 1;
	conn_opts.username = opts.token;
	conn_opts.password = opts.appid;
	
	myconnect(&client, &conn_opts);
	
	rc = MQTTClient_subscribe(client, topic, opts.qos);

	while (!toStop)
	{
		char* topicName = NULL;
		int topicLen;
		MQTTClient_message* message = NULL;
		
		rc = MQTTClient_receive(client, &topicName, &topicLen, &message, 1000);
		if (message)
		{
			if (opts.showtopics)
				printf("%s\t", topicName);
      if (opts.nodelimiter)
				printf("%.*s", message->payloadlen, (char*)message->payload);
			else
				printf("%.*s%s", message->payloadlen, (char*)message->payload, opts.delimiter);
			fflush(stdout);
			MQTTClient_freeMessage(&message);
			MQTTClient_free(topicName);
		}
		if (rc != 0)
			myconnect(&client, &conn_opts);
	}
	
	printf("Stopping\n");

	MQTTClient_disconnect(client, 0);

 	MQTTClient_destroy(&client);

	return 0;
}
