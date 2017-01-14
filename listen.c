#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include<wiringPi.h>


#include <json.h>

#include "pubnub.h"
#include "pubnub-sync.h"

#define PUBLISH_KEY "Write Here"
#define SUBSCRIBE_KEY "Write Here"


struct pubnub_sync *_sync;
struct pubnub *p;
json_object *msg;
char *buff;


char * readPubnub ()
{
	/* Subscribe */
/* 1 */		const char *channels[] = { "my_channel", "demo_channel" };
/* 2 */		pubnub_subscribe_multi(
				/* struct pubnub */ p,
				/* list of channels */ channels,
				/* number of listed channels */ 2,
				/* default timeout */ -1,
				/* callback; sync needs NULL! */ NULL,
				/* callback data */ NULL);
		if (pubnub_sync_last_result(_sync) != PNR_OK)
			return EXIT_FAILURE;
		msg = pubnub_sync_last_response(_sync);
		if (json_object_array_length(msg) == 0) {
			printf("pubnub subscribe ok, no news\n");
		} else {
			char **msg_channels = pubnub_sync_last_channels(_sync);
			for (int i = 0; i < json_object_array_length(msg); i++) {
				json_object *msg1 = json_object_array_get_idx(msg, i);
				printf("pubnub subscribe [%s]: %s\n", msg_channels[i], buff = (char *)json_object_get_string(msg1));

			}
		}
		return buff;
        
}


void PubNubInit ()
{
        _sync = pubnub_sync_init();

        p = pubnub_init(
                        /* publish_key */ PUBLISH_KEY,
                        /* subscribe_key */ SUBSCRIBE_KEY,
                        /* pubnub_callbacks */ &pubnub_sync_callbacks,
                        /* pubnub_callbacks data */ _sync);

}
void led()
{
        wiringPiSetup();
        pinMode(8,OUTPUT);
//        while(1)
//      {
                digitalWrite(8,LOW);
                delay(1000);
                digitalWrite(8,HIGH);
                delay(1000);
//      }
}


int main(void)
{
	char *readbuff;
	PubNubInit ();
	readbuff = readPubnub ();

	rintf ("readbuff = %s\n",readbuff);
//	rintf ("readbuff = %s\n",readbuff);
}

