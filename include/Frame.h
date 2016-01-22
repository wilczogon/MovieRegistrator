#ifndef FRAME_H
#define FRAME_H
#include <iostream>
#include <vector>
#include <opencv/cv.h>


class Frame
{
    public:
        Frame(cv::Mat frameData);
        virtual ~Frame();
        float getRedMean();
        float getGreenMean();
        float getBlueMean();
        cv::Mat getData();
        int getX();
        int getY();
    protected:
    private:
        int x, y;
        float redMean = -1, greenMean = -1, blueMean = -1;
        cv::Mat data;
};

#endif // FRAME_H
