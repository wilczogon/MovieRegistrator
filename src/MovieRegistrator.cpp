#include "MovieRegistrator.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <limits>

int MovieRegistrator::countOptimalShift(Movie* movie1, Movie* movie2){
    return countOptimalShift(movie1, movie2, 100, -movie2->getFramesNo(), movie1->getFramesNo());
}

int MovieRegistrator::countOptimalShift(Movie* movie1, Movie* movie2, int step, int start, int end){
    if(end < start)
        throw "End cannot be lower than start! start: ";

    if(step < 1){
        float minIndice = start;
        float minDist = std::numeric_limits<float>::max();
        for(int i = start; i<end; ++i){
            int val = countDistance(movie1, movie2, i);
            if(val < minDist){
                minDist = val;
                minIndice = i;
            }
        }

        return minIndice;
    }

    float minIndice = start;
    float minDist = std::numeric_limits<float>::max();
    for(int i = start; i<end; i+=step){
        float val = countDistance(movie1, movie2, i);
        if(val < minDist){
            minDist = val;
            minIndice = i;
        }
    }

    return countOptimalShift(movie1, movie2, step/10, fmax(start, minIndice - step), fmin(end, minIndice + step));
}

float MovieRegistrator::countDistance(Movie* movie1, Movie* movie2, int shift){
    int start1 = (shift > 0 ? shift : 0);
    int start2 = (shift > 0 ? 0 : -shift);
    int length = countIntersectionSize(movie1, movie2, shift);

    float distance = 0;

    for(int i = 0; i < length; ++i){
        distance += fabs(movie1->getCumulativeRed()[start1 + i] - movie2->getCumulativeRed()[start2 + i]);
        distance += fabs(movie1->getCumulativeGreen()[start1 + i] - movie2->getCumulativeGreen()[start2 + i]);
        distance += fabs(movie1->getCumulativeBlue()[start1 + i] - movie2->getCumulativeBlue()[start2 + i]);
    }

    if(distance < 0)
        throw "Distance lower then 0!";

    return distance/length;
}

int MovieRegistrator::countIntersectionSize(Movie* movie1, Movie* movie2, int shift){
    if(shift > 0){
        return fmin(movie1->getFramesNo() - shift, movie2->getFramesNo());
    } else{
        return fmin(movie2->getFramesNo() + shift, movie1->getFramesNo());
    }
}

Movie* MovieRegistrator::trimMovie(Movie* movie, int shift, int length){
    std::vector<Frame*> frames;
    for(int i = shift; i<shift+length; ++i){
        frames.push_back(movie->getFrame(i));
    }
    return new Movie(frames, movie->getFps(), movie->getFourcc());
}

Movie* MovieRegistrator::glueMovies(Movie* movie1, Movie* movie2){
    if(movie1->getFramesNo() != movie2->getFramesNo())
        throw "Only movies with the same number of frames can be glued!";

    if(movie1->getFps() != movie2->getFps()) //TODO do something about it
        throw "Two different fps values!";

    std::vector<Frame*> frames;
    for(int i = 0; i<movie1->getFramesNo(); ++i){
        cv::Mat frame;
        movie1->getFrame(i)->getData().copyTo(frame);
        cv::hconcat(frame, movie1->getFrame(i)->getData(), frame);
        frames.push_back(new Frame(frame));
    }

    return new Movie(frames, movie1->getFps(), movie1->getFourcc());
}
