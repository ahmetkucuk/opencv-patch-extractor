#include <opencv2/core/core.hpp>
#include <cv.h>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>
#include <stdio.h>
#include "string.h"
#include "FileReader.cpp"

using namespace std;
using namespace cv;


/*
*
*
*/
cv::Mat readJP2Image(string pathToImage) {
    
    
    cv::Mat image;
    image = imread(pathToImage, 0);   // Read the file

    if(! image.data )                           // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl;
    }
    return image;
}

int saveImageRegion (Mat &image, int x, int y, int w, int h, string imagePath) {
    
    Mat roi(image, Rect(x,y,w,h));
    IplImage ipl_from_mat((IplImage)roi);
    
    cvSaveImage((imagePath).c_str(), &ipl_from_mat);
    return 1;
}


int extractRegionForEvent(Event &event, string outputDir, Mat &image) {

    string imageName = event.getType() + "_" + event.getBbox() + "_" + event.getStartFile() + ".png";//+ std::to_string(event.getUpperLeftX()) + "_" + std::to_string(event.getUpperLeftY()) + "_" + std::to_string(event.getWidth()) + "_" + std::to_string(event.getHeight()) + "_" + event.getStartFile() + ".jpg";
    if(event.isCoordianteValid(4096, 4096)) { // 4096 or image.cols.size
        saveImageRegion(image, event.getUpperLeftX(), event.getUpperLeftY(), event.getWidth(), event.getHeight(),  outputDir + imageName );
    } else {
        cout << "Even coordinate error: " << event.toString() << endl;
    }
    return 1;
}



int main( int argc, char** argv )
{


    string filein = argv[1];
    string imageDirs = argv[2];
    string outputDirBase = argv[3];
    string imagePathDirs = argv[4];
    int offset = atoi(argv[5]);

    FileReader dirReader(imageDirs);

    map<string, string> dirMap = dirReader.getImageDirMap(imagePathDirs);

    FileReader reader(filein);
    Event event = *reader.nextEvent();
    for(int i = 0; i < offset; i++) {
        event = *reader.nextEvent();
    }

    string lastImageName = "";
    Mat image;
    while(&event != NULL) {
        //cout << "event id " << dirMap[event.getStartFile()] <<  "\n" << endl;
        if (lastImageName.compare(event.getStartFile()) != 0) {
            image = readJP2Image(dirMap[event.getStartFile()]);
            lastImageName = event.getStartFile();
            cout << lastImageName << endl;
        }
        string outputDir = outputDirBase + "/" + event.getType() + "/" + event.getChannel() + "/";
        cout << outputDir << endl;
        system( ("mkdir -p " + outputDir).c_str());
        extractRegionForEvent(event, outputDir, image);
        event = *reader.nextEvent();
    }


    //clock_t beginRead = clock();
    //cv::Mat image = readJP2Image("image.jp2");
    //clock_t endRead = clock();
//
//
    //Mat roi(image, Rect(1000,1000,1000,1000));
    //cout << roi << endl;
    //IplImage ipl_from_mat((IplImage)roi);
    //cvSaveImage("output/image.jpg", &ipl_from_mat);
//
    //double elapsed_secs_read = double(beginRead - endRead) / CLOCKS_PER_SEC;
    //
    //cout << "Total Time Elapsed for Read: " << elapsed_secs_read << endl;
    return 0;
}