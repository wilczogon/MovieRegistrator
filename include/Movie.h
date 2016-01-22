#ifndef MOVIE_H
#define MOVIE_H
#include <Frame.h>

class Movie
{
    public:
        Movie(char* filename);
        Movie(std::vector<Frame*> frames, double fps, int fourcc);
        virtual ~Movie();
        Frame* getFrame(int i);
        int getFramesNo();
        double getFps();
        int getFourcc();
        float* getCumulativeRed();
        float* getCumulativeGreen();
        float* getCumulativeBlue();
        void save(char* filename);
    protected:
    private:
        int frameNo;
        double fps;
        int fourcc;
        std::vector<Frame*> frames;
        float *cumulativeRed = NULL, *cumulativeGreen = NULL, *cumulativeBlue = NULL;
};

#endif // MOVIE_H
