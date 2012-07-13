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

void* threadStart(void* params) {
	Worker worker(comicQueue);
	workers.push_back(&worker);
	worker.process();
	return NULL;
}

int main(int argc, char **argv) {
	pthread_t thread[NUMTHREADS];
	
	for (int i = 0; i < NUMTHREADS; ++i) {
		int rc = pthread_create(&thread[i], NULL, threadStart, NULL);
		//check for errors
	}
	
	Receiver receiver(comicQueue);
	receiver.start();
	
	cout << "Press any key to stop" << endl;
	cin.ignore();
	cout << "STOP! Hammer time." << endl;
	
	receiver.stop();
	Worker::turnOff();
	
	for (int i = 0; i < NUMTHREADS; ++i) {
		int rc = pthread_join(thread[i], NULL);
		//check for errors
	}
	
	return 0;
}
