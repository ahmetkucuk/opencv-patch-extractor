#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "Event.cpp"
#include "stdlib.h"
#include "string.h"

using namespace std;

#define EVENT_ID 0
#define EVENT_TYPE 1
#define EVENT_STIME 2
#define EVENT_ETIME 3
#define EVENT_CHANNEL 4
#define EVENT_BBOX 5
#define EVENT_SFILE 6
#define EVENT_MFILE 7
#define EVENT_EFILE 8

class FileReader;

class FileReader {
	std::ifstream readStream;
	public:
		inline string next();
		inline map<string, string> getImageDirMap(std::string imageBasePath);
		inline Event *nextEvent();
		inline std::vector<std::string> split(std::string str,std::string sep);
		inline FileReader(std::string filePath);
		void split2(const std::string &s, char delim, vector<string> &elems) {
		    std::stringstream ss(s);
		    std::string item;
		    while (std::getline(ss, item, delim)) {
		        elems.push_back(item);
		    }
		}
};

FileReader::FileReader (std::string filePath) {

	readStream.open(filePath.c_str());
}

std::string FileReader::next () {
	std::string line;
	std::getline(readStream, line);
  	return line;
}

map<string, string> FileReader::getImageDirMap(std::string imageBasePath) {

	map<string, string> result;
	string line;
	while(!(line = next()).empty()) {
		std::vector<std::string> arr;
		arr=split(line,"\t");
		result[arr[0]] = imageBasePath + arr[1];
	}
	return result;
}

Event *FileReader::nextEvent () {

	std::string line;
	std::getline(readStream, line);
	if(line.empty()) {
		Event *temp = NULL;
		return temp;
	}

	std::size_t found = line.find("bbox");
	if (found != std::string::npos) {
		std::getline(readStream, line);
	}

	std::vector<std::string> arr;
    //arr=split(line,"\t");
    split2(line, '\t', arr);

    //unsigned int i = 0;
    
    //i++;
//
    //cout << coordinates.size() << endl;
    //cout << coordinates.at(i) << endl;


  	
  	
  	
  	Event *e = new Event(arr[EVENT_ID], arr[EVENT_TYPE], arr[EVENT_STIME], arr[EVENT_ETIME], arr[EVENT_CHANNEL], arr[EVENT_BBOX], arr[EVENT_SFILE], arr[EVENT_MFILE], arr[EVENT_EFILE]);
	

    string bbox = arr[EVENT_BBOX];

	vector<string> coordinates;
	split2(bbox, '-', coordinates);

	if(coordinates.size() == 4) {
	    int x = atoi(coordinates.at(0).c_str());
	    int y = atoi(coordinates.at(1).c_str());
	    int w = atoi(coordinates.at(2).c_str());
	    int h = atoi(coordinates.at(3).c_str());
		(*e).setRegion(x, y, w, h);
	}
	return e;
}

std::vector<std::string> FileReader::split(std::string str,std::string sep){
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    std::vector<std::string> arr;
    current=strtok(cstr,sep.c_str());
    while(current!=NULL){
        arr.push_back(current);
        current=strtok(NULL,sep.c_str());
    }
    return arr;
}