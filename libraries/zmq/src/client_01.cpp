/*************
 *	This exmaple demonstrates anout using zmq library
 *	
 *	Pubsub envelope publisher
 *	Note that the zhelpers.h file also provides s_sendmore
 *
 * ***********/

#include "server.hpp"
#include "common.hpp"

int main (void)
{
	//  Prepare our context and publisher
	void *context = zmq_ctx_new ();
	void *publisher = zmq_socket (context, ZMQ_PUB);
	zmq_bind (publisher, "tcp://*:5563");
		
	int i = 100;

	while (1) {
		//  Write two messages, each with an envelope and content
		char filter[16] = {0};
		char msg_buf[128] = {0};

		memset(filter, 0, 16);
		snprintf(filter, 15, "%s", "CLI_01_A");
		zmq_send (publisher, filter, strlen(filter), ZMQ_SNDMORE);
		//s_sendmore (publisher, "CLI_01_A");
		memset(msg_buf, 0, 128);
		snprintf(msg_buf, 127, "Message from CLI_01_A:      Not expecting this:	%03d", ++i);
		zmq_send (publisher, msg_buf, strlen(msg_buf), 0);
		//s_send (publisher, msg_buf);
		
		memset(filter, 0, 16);
		snprintf(filter, 15, "%s", "CLI_01_B");
		zmq_send (publisher, filter, strlen(filter), ZMQ_SNDMORE);
		//s_sendmore (publisher, "CLI_01_B");
		memset(msg_buf, 0, 128);
		snprintf(msg_buf, 127, "Message from CLI_01_B:      Expecting this:	%03d", ++i);
		zmq_send (publisher, msg_buf, strlen(msg_buf), 0);
		//s_send (publisher, "Message from CLI_01_B:	Expecting this");

		sleep (1);
	}
	//  We never get here, but clean up anyhow
	zmq_close (publisher);
	zmq_ctx_destroy (context);
	return 0;
}

/******
 *	END OF FILE
 * ******/
