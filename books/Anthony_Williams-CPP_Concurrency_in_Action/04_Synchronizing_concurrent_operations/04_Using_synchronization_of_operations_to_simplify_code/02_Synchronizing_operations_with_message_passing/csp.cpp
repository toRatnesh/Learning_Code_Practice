/*****

References
    Anthony Williams - C++ Concurrency in Action

    https://en.cppreference.com/w/cpp/experimental/concurrency/promise
    https://en.cppreference.com/w/cpp/experimental/future
    https://en.cppreference.com/w/cpp/experimental/shared_future

4.4 Using synchronization of operations to simplify code
	Rather than sharing data directly between threads, each task can be provided with the data it needs, and the result can be disseminated to any other threads that need it through the use of futures.


4.4.2 Synchronizing operations with message passing
	CSP (Communicating Sequential Processes)
		In CSP, threads are conceptually entirely separate, with no shared data but with communication channels that allow messages to be passed between them.
		Used in Erlang programming language and MPI (Message Passing Interface; http://www.mpi-forum.org/) 
		
	Idea of CSP is simple: if there’s no shared data, each thread can be reasoned about entirely independently, purely on the basis of how it behaves in response to the messages that it received.
	One way to write such threads would be to formalize this and implement a Finite State Machine model, but this isn’t the only way; the state machine can be implicit in the structure of the application.
	
	One way to model the ATM logic would be as a state machine. In each state, the thread waits for an acceptable message, which it then processes. This may result in transitioning to a new state, and the cycle continues.
	
	This style of program design is called the Actor model—there are several discrete actors in the system (each running on a separate thread), which send messages to each other to perform the task at hand, and there’s no shared state except that which is directly passed via messages.

**********/


int main() {

    return 0;
}

/*****
    END OF FILE
**********/



