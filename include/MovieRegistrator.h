#ifndef MOVIEREGISTRATOR_H
#define MOVIEREGISTRATOR_H
#include <Movie.h>

class MovieRegistrator
{
    public:
        MovieRegistrator();
        virtual ~MovieRegistrator();
        static int countOptimalShift(Movie* movie1, Movie* movie2);
        static float countDistance(Movie* movie1, Movie* movie2, int shift);
        static int countIntersectionSize(Movie* movie1, Movie* movie2, int shift);
        static Movie* trimMovie(Movie* movie, int shift, int length);
        static Movie* glueMovies(Movie* movie1, Movie* movie2);
    protected:
    private:
        static int countOptimalShift(Movie* movie1, Movie* movie2, int step, int start, int end);
};

#endif // MOVIEREGISTRATOR_H
