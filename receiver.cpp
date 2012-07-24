#include "receiver.h"
#include <sstream>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include "pthread.h"

using namespace std;

typedef unsigned short ushort;

bool Receiver::done = false;

/*
 * Initializes and creates a listener for http requests.
 */
Receiver::Receiver(ushort port) {
	httpd = 0;
	struct sockaddr_in name;
	httpd = socket(PF_INET, SOCK_STREAM, 0);
	if(httpd == -1) {
		cerr << "unable to create socket" << endl;
		exit(-1);
	}

	name.sin_family = AF_INET;
	name.sin_port = htons(port);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(httpd, (struct sockaddr *)&name, sizeof(name)) < 0) {
		cerr << "unable to bind socket" << endl;
		exit(-1);
	}

	if (listen(httpd, 10) < 0) {
		cerr << "unable to listen on socket" << endl;
		exit(-1);
	}
}

/*
 * This is very brittle. It assumes all http requests are correct. 
 * It brute force parses the request and enqueues it.
 */
void Receiver::handleEvent(int clientSocket) {
	char buf[65535]; //max socket buffer size
	stringstream ss;
	
	pollfd fd;
	fd.fd = clientSocket;
	fd.events = POLLIN;
	
	for(;;) {
		
		poll(&fd, 1, 0);
		
		if(!(fd.revents & POLLIN)) { //todo: check size of http request rather than reading buffer entirely
			break;
		}
		if(read(clientSocket, buf, sizeof(buf)) <= 0) {
			break;
		}

		ss << buf;
	}
	
	string request = ss.str();
	
	for(int i = 0, j = 0;;) {
		if(j > request.size()) {
			cerr << "couldn't parse http request" << endl;
			return;
		}
		if(request[j++] = '\n') {
			if(++i == 6) {
				request.erase(0, --j);
				break;
			}
		}
	}
	
	size_t pos = request.find("=");
	pos = request.find("=", pos + 1);
	request.erase(0, pos);
	
	const char* file2 = request.c_str();
	
	rawData file = new unsigned char[request.size()];
	
	for(int i = 0; i < request.size(); ++i) {
		file[i] = file2[i];
	}
	
	Queue::getQueue()->enqueue(file, sizeof(file), clientSocket);
}

void Receiver::start() {
	auto rc = pthread_create(&thread, NULL, process, (void*)httpd);
	//check for errors
}

void Receiver::stop() {
	done = true;
	pthread_join(thread, NULL);
}

//constantly checks for new http requests
void* Receiver::process(void* params) {
	int serverSock = (long int)params;
	int clientSock = -1;
	
	for(;;) {
		clientSock = accept(serverSock, NULL, 0);
		if (clientSock == -1) {
			//error
			continue;
		}
		handleEvent(clientSock);
	}
	
	pthread_exit(NULL);
}