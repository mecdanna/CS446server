#include "receiver.h"

using namespace std;
using namespace mongoose;

Receiver::Receiver(Queue& queue) : queue(queue) {
	setOption("listening_ports", "8080");
	setOption("num_threads", "3");
};

bool Receiver::handleEvent(ServerHandlingEvent eventCode, MongooseConnection &connection, const MongooseRequest &request, MongooseResponse &response) {
	string fileSz;
	if(!request.getVar("fileSz", fileSz)) {
		//log some kind of error
		return false;
	}
	
	size_t size = atoi(fileSz.c_str());
	void* data;
	if(!request.getData("file", data, size)) {
		return false;
	}
}
	