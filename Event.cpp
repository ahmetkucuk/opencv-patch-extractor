#include <string>
#include <string.h>

using namespace std;
class Event;

class Event {
	std::string id;
	std::string type;
	std::string sTime;
	std::string eTime;
	std::string channel;
	std::string bbox;
	std::string sFile;
	std::string mFile;
	std::string eFile;

	int upperLeftX, upperLeftY, width, height;
	public:
		void setRegion(int sX, int sY, int w, int h) {
			upperLeftX = sX;
			upperLeftY = sY;
			width = w;
			height = h;
		}

		bool isCoordianteValid(int maxWidth, int maxHeight) {

			if ( width < 0 || height < 0) {
				return false;
			}
			if(upperLeftX + width > maxWidth || upperLeftY + height > maxHeight) {
				return false;
			}
			return true;
		}

		int getUpperLeftX() {
			return upperLeftX;
		}

		int getUpperLeftY() {
			return upperLeftY;
		}

		int getWidth() {
			return width;
		}

		int getHeight() {
			return height;
		}


		string mgetEventId() {
			return id;
		}

		string getType() {
			return type;
		}

		string getStartTime() {
			return sTime;
		}

		string getEndTime() {
			return eTime;
		}

		string getChannel() {
			return channel;
		}

		string getBbox() {
			return bbox;
		}

		string getStartFile() {
			return sFile;
		}

		string getMidFile() {
			return mFile;
		}

		string getEndFile() {
			return eFile;
		}

		string toString() {
			return "id: " + id + " type: " + type + " bbox: " + bbox;
		}
		inline Event(string eventId, string eType, string startTime, string endTime, string c, string boundingBox, string startFile, string midFile, string endFile);
};

Event::Event (string eventId, string eType, string startTime, string endTime, string c, string boundingBox, string startFile, string midFile, string endFile) {
	id = eventId;
	type = eType;
	sTime = startTime;
	eTime = endTime;
	channel = c;
	bbox = boundingBox;
	sFile = startFile;
	mFile = midFile;
	eFile = endFile;
}
