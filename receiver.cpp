#include "receiver.h"
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include "pthread.h"

using namespace std;

typedef unsigned short ushort;

bool Receiver::done = false;

Receiver::Receiver(ushort port) {
	httpd = 0;
	struct sockaddr_in name;
	httpd = socket(PF_INET, SOCK_STREAM, 0);
	if(httpd == -1) {
		//error	
	}

	name.sin_family = AF_INET;
	name.sin_port = htons(port);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(httpd, (struct sockaddr *)&name, sizeof(name)) < 0) {
		//error
	}

	if (listen(httpd, 10) < 0) {
		//error
	}
}

void Receiver::handleEvent(int clientSocket) {
	char buf[65535];
	stringstream ss;
	
	pollfd fd;
	fd.fd = clientSocket;
	fd.events = POLLIN;
	
	for(;;) {
		
		poll(&fd, 1, 0);
		
		if(!(fd.revents & POLLIN)) {
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
			//error
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