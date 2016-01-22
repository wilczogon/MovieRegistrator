#include "Frame.h"
#include <opencv/cv.h>
#include <numeric>

Frame::Frame(cv::Mat frameData)
{
    data = frameData;
    cv::Mat channels[3];
    cv::split(data, channels);

    std::vector<std::vector<uchar> > array;
    for(int k = 0; k<3; ++k){
        std::vector<uchar> vec;
        if (channels[k].isContinuous()) {
            vec.assign(channels[k].datastart, channels[k].dataend);
        } else {
            for (int i = 0; i < channels[k].rows; ++i) {
                vec.insert(vec.end(), channels[k].ptr<uchar>(i), channels[k].ptr<uchar>(i)+channels[k].cols);
            }
        }
        array.push_back(vec);
    }

    x = frameData.cols;
    y = frameData.rows;

    redMean = std::accumulate(array[0].begin(), array[0].end(), 0) / (float)array[0].size();
    greenMean = std::accumulate(array[1].begin(), array[1].end(), 0) / (float)array[1].size();
    blueMean = std::accumulate(array[2].begin(), array[2].end(), 0) / (float)array[2].size();
}

Frame::~Frame()
{
    //dtor
}

float Frame::getRedMean(){
    return redMean;
}

float Frame::getGreenMean(){
    return greenMean;
}

float Frame::getBlueMean(){
    return blueMean;
}

cv::Mat Frame::getData(){
    return data;
}

int Frame::getX(){
    return x;
}

int Frame::getY(){
    return y;
}
