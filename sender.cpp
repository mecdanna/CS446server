#include "sender.h"
#include <sstream>

using namespace std;
using namespace mongoose;

void Sender::sendToClient(std::vector<ComicFrames>& frames, MongooseResponse& response) {
	response.setConnectionAlive(false);
	response.setContentType("text");
	response.setStatus(200);
	
	stringstream encode;

	for(auto page : frames) {
		int j = 0;
		encode << "<page=" << j << ">";
		for(int i = 0; i < page.count(); ++i) {
			comicFrame frame = page[i];
			
			encode	<< "<frame=" << i << ">"
					<< "<x>" + frame.xPos() << "</x>"
					<< "<y>" + frame.yPos() << "</y>"
					<< "<w>" + frame.width() << "</w>"
					<< "<h>" + frame.height() << "</h>"
					<< "</frame>";
		}
		encode << "</page>";
	}
	
	response.addContent(encode.str());
	response.write();
}
