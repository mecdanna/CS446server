#include "sender.h"
#include "sys/socket.h"
#include <sstream>

using namespace std;

void Sender::sendToClient(std::vector<ComicFrames>& frames, int response) {
	
	stringstream encode;

	encode << "<comic>";
	for(auto page : frames) {
		int j = 0;
		encode << "<page>";
		for(int i = 0; i < page.count(); ++i) {
			comicFrame frame = page[i];
			
			encode	<< "<frame>"
					<< "<x>" + frame.xPos() << "</x>"
					<< "<y>" + frame.yPos() << "</y>"
					<< "<w>" + frame.width() << "</w>"
					<< "<h>" + frame.height() << "</h>"
					<< "</frame>";
		}
		encode << "</page>";
	}
	encode << "</comic>";
	
	const char* buf = encode.str().c_str();
	
	send(response, buf, encode.str().size(), 0);
	
}
