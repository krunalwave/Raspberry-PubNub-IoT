#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <json.h>

#include "pubnub.h"
#include "pubnub-sync.h"

#define PUBLISH_KEY "Write Here"
#define SUBSCRIBE_KEY "Write Here"

/* Declaration of PubNub Variables */
struct pubnub_sync *_sync;
struct pubnub *p;
json_object *msg;

int writePubnub (char *mymsg)
{
	/* Publish */


	msg = json_object_new_object();
	json_object_object_add(msg, "str", json_object_new_string(mymsg));

/* 1 */	pubnub_publish(
			/* struct pubnub */ p,
			/* channel name*/ "my_channel",
			/* message */ msg,
			/* default timeout */ -1,
			/* callback; sync needs NULL! */ NULL,
			/* callback data */ NULL);

	json_object_put(msg);

	if (pubnub_sync_last_result(_sync) != PNR_OK)
		return EXIT_FAILURE;
	msg = pubnub_sync_last_response(_sync);
	json_object_put(msg);
}


int readPubNubHistory ()
{
	/* History */

	pubnub_history(
			/* struct pubnub */ p,
			/* channel */ "my_channel",
			/* messages */ 10,
			/* default timeout */ -1,
			/* callback; sync needs NULL! */ NULL,
			/* callback data */ NULL);
	if (pubnub_sync_last_result(_sync) != PNR_OK)
		return EXIT_FAILURE;
	msg = pubnub_sync_last_response(_sync);
	printf("pubnub history ok: %s\n", json_object_get_string(msg));
	json_object_put(msg);
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



int main ()
{
	PubNubInit ();
	writePubnub ("Krunal");
	return 0;
}




