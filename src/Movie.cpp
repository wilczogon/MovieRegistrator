#include "Movie.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/opencv.hpp>

Movie::Movie(char* filename)
{
    cv::VideoCapture capture(filename);

    if(!capture.isOpened())
        throw "Movie couldn't be opened!";

    while(true){
        cv::Mat frameData;
        bool cont = capture.read(frameData);
        if(!cont)
            break;
        frames.push_back(new Frame(frameData));
    }

    frameNo = frames.size();
    fps = capture.get(CV_CAP_PROP_FPS);
    fourcc = capture.get(CV_CAP_PROP_FOURCC);
    capture.release();
}

Movie::Movie(std::vector<Frame*> frames, double fps, int fourcc){
    this->frames = frames;
    this->fps = fps;
    this->fourcc = fourcc;
    this->frameNo = frames.size();
}

Movie::~Movie()
{
    //dtor
}

Frame* Movie::getFrame(int i){
    if(i >= frameNo)
        throw "Trying access not existing frame!";
    return frames[i];
}

int Movie::getFramesNo(){
    return frameNo;
}

double Movie::getFps(){
    return fps;
}

int Movie::getFourcc(){
    return fourcc;
}

float* Movie::getCumulativeRed(){
    if(cumulativeRed == NULL){
        cumulativeRed = (float*)malloc(frameNo*sizeof(float));
        cumulativeRed[0] = getFrame(0)->getRedMean();
        for(int i = 1; i<frameNo; ++i){
            cumulativeRed[i] = cumulativeRed[i-1] + getFrame(i)->getRedMean();
        }
    }

    return cumulativeRed;
}

float* Movie::getCumulativeGreen(){
    if(cumulativeGreen == NULL){
        cumulativeGreen = (float*)malloc(frameNo*sizeof(float));
        cumulativeGreen[0] = getFrame(0)->getGreenMean();
        for(int i = 1; i<frameNo; ++i)
            cumulativeGreen[i] = cumulativeGreen[i-1] + getFrame(i)->getGreenMean();
    }

    return cumulativeGreen;
}

float* Movie::getCumulativeBlue(){
    if(cumulativeBlue == NULL){
        cumulativeBlue = (float*)malloc(frameNo*sizeof(float));
        cumulativeBlue[0] = getFrame(0)->getBlueMean();
        for(int i = 1; i<frameNo; ++i)
            cumulativeBlue[i] = cumulativeBlue[i-1] + getFrame(i)->getBlueMean();
    }

    return cumulativeBlue;
}

void Movie::save(char* filename){
    cv::VideoWriter writer;
    bool opened = writer.open(filename, fourcc, fps, cv::Size(getFrame(0)->getX(), getFrame(0)->getY()));

    if(!opened)
        throw "Cannot create files!";

    for(int i = 0; i<frameNo; ++i)
        writer.write(getFrame(i)->getData());

    //writer.release();
}
