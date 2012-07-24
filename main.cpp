#include "receiver.h"
#include "queue.h"
#include "worker.h"
#define _MULTI_THREADED
#include "pthread.h"
#include <iostream>

#define NUMTHREADS 10

using namespace std;

static Queue comicQueue;
vector<Worker*> workers(NUMTHREADS);

//need a static starting point for [ROT YOU!!!] pthreads
void* threadStart(void* params) {
	Worker worker(comicQueue);
	workers.push_back(&worker);
	worker.process();
	return NULL;
}

int main(int argc, char **argv) {
	pthread_t thread[NUMTHREADS];
	
	//start the workers
	for (int i = 0; i < NUMTHREADS; ++i) {
		int rc = pthread_create(&thread[i], NULL, threadStart, NULL);
		//check for errors
	}
	
	//start the receiver
	Receiver receiver(80);
	receiver.start();
	
	cout << "Press Enter to stop" << endl;
	cin.ignore();
	cout << "STOP! Hammer time." << endl;
	
	receiver.stop();
	
	//end all the workers
	Worker::turnOff();
	
	for (int i = 0; i < NUMTHREADS; ++i) {
		int rc = pthread_join(thread[i], NULL);
		//check for errors
	}
	
	return 0;
}
