
#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "/usr/local/include/zmq.h"


//static void rtCmDirRecCB(std::shared_ptr<void> info, unsigned len);
//void rtCmDirRecCB(std::shared_ptr<void> info, unsigned len);


//  Receive 0MQ string from socket and convert into C string
//  Caller must free returned string. Returns NULL if the context
//  is being terminated.
static char *
s_recv (void *socket) {
	char buffer [256];
	int size = zmq_recv (socket, buffer, 255, 0);
	if (size == -1)
		return NULL;
	buffer[size] = '\0';

#if (defined (WIN32))
	return strdup (buffer);
#else
	return strndup (buffer, sizeof(buffer) - 1);
#endif

	// remember that the strdup family of functions use malloc/alloc for space for the new string.  It must be manually
	// freed when you are done with it.  Failure to do so will allow a heap attack.
}



//  Convert C string to 0MQ string and send to socket
static int
s_send (void *socket, char *string) {
	int size = zmq_send (socket, string, strlen (string), 0);
	return size;
}

//  Sends string as 0MQ string, as multipart non-terminal
static int
s_sendmore (void *socket, char *string) {
	int size = zmq_send (socket, string, strlen (string), ZMQ_SNDMORE);
	return size;
}

#endif 


