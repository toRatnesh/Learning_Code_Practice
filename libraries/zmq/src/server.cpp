/**************
 *	This example demonstrates about the uses of zmq library
 *
 *	Pubsub envelope subscriber
 *
 * ***********/

#include "client.hpp"
#include "common.hpp"
#include <cassert>

int main (void)
{
	//  Prepare our context and subscriber
	void *context = zmq_ctx_new ();
	void *subscriber = zmq_socket (context, ZMQ_SUB);

	zmq_connect (subscriber, "tcp://localhost:5563");
	zmq_connect (subscriber, "tcp://localhost:5565");

	zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, "CLI_01_B", strlen("CLI_01_B"));
	zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, "CLI_02_A", strlen("CLI_02_A"));

	while (1) {

		int rc;

		zmq_msg_t message;
		size_t message_size;
		int size = 0;

		rc = zmq_msg_init (&message);
		assert (rc == 0);

		puts ("----------------------------------------");

		size = zmq_msg_recv (&message, subscriber, 0);
		assert (size >= 0);

		//  Dump the message as text or binary
		if(NULL == (char*)zmq_msg_data (&message)) {
			printf("Message buffer filter not allocated properly\n");
			return -1;
		}

		message_size = zmq_msg_size(&message);
		assert(0 <= message_size);

		char buffer_filter[message_size + 1] = {0};
		memset(buffer_filter, 0, message_size + 1);

		printf("size : %d 	message_size:%zu \n", size, message_size);	fflush(stdout);
		memcpy(buffer_filter, (char*)zmq_msg_data (&message), message_size);
		printf("%s\n", buffer_filter); fflush(stdout);


		if(zmq_msg_more(&message)) {
			size = zmq_msg_recv (&message, subscriber, 0);
			assert (size >= 0);

			//  Dump the message as text or binary
			if(NULL == (char*)zmq_msg_data (&message)) {
				printf("Message buffer not allocated properly\n");
				return -1;
			}

			message_size = zmq_msg_size(&message);
			assert(0 <= message_size);

			char buffer[message_size + 1] = {0};
			memset(buffer, 0, message_size + 1);

			printf("size : %d 	message_size:%zu \n", size, message_size);	fflush(stdout);
			memcpy(buffer, (char*)zmq_msg_data (&message), message_size);
			printf("%s\n", buffer); fflush(stdout);
			puts ("----------------------------------------");

		}

		rc = zmq_msg_close (&message);
		assert (rc == 0);	
		printf("\n");

		/*
		   int rc;

		   zmq_msg_t message;
		   size_t message_size;

		   rc = zmq_msg_init (&message);
		   assert (rc == 0);

		   puts ("----------------------------------------");
		//  Process all parts of the message
		do {
		int size = zmq_msg_recv (&message, subscriber, 0);
		assert (size >= 0);

		//  Dump the message as text or binary
		if(NULL == (char*)zmq_msg_data (&message)) {
		printf("Message buffer not allocated properly\n");
		return -1;
		}


		message_size = zmq_msg_size(&message);
		assert(0 <= message_size);

		char buffer[message_size + 1] = {0};
		memset(buffer, 0, message_size + 1);

		printf("size : %d 	message_size:%zu \n", size, message_size);	fflush(stdout);
		memcpy(buffer, (char*)zmq_msg_data (&message), message_size);
		printf("%s\n", buffer); fflush(stdout);

		} while (zmq_msg_more (&message));
		rc = zmq_msg_close (&message);
		assert (rc == 0);	
		printf("\n");

*/
		/*
		   char buffer [256];
		   int size = 0;

		   memset(buffer, 0, 256);
		   size = zmq_recv (subscriber, buffer, 255, 0);
		   if (size == -1)
		   return size;
		   buffer[size] = '\0';
		   printf("[%s] ", buffer); fflush(stdout);


		   memset(buffer, 0, 256);
		   size = zmq_recv (subscriber, buffer, 255, 0);
		   if (size == -1)
		   return size;
		   buffer[size] = '\0';
		   printf("%s\n", buffer);	fflush(stdout);
		   */

		/*
		//  Read envelope with address
		char *address = s_recv (subscriber);
		//  Read message contents
		char *contents = s_recv (subscriber);
		printf ("[%s] %s\n", address, contents);

		free (address);
		free (contents);
		*/

	}
	//  We never get here, but clean up anyhow
	zmq_close (subscriber);
	zmq_ctx_destroy (context);

	return 0;
}

/*******
 *	END OF FILE
 * *****/
