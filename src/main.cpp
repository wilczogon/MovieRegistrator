#include <iostream>
#include <Movie.h>
#include <MovieRegistrator.h>

void printInstruction(){
    std::cout << "Incorrect format!\n\nPlease add parameters:\n<1st movie filepath> <2nd movie filepath> <1st movie result filepath> <2nd movie result filepath>\nOR\n<1st movie filepath> <2nd movie filepath> <movie result filepath>\n\n";
}

int main(int argc, char** args){
    char* movie1Name = args[1];
    char* movie2Name = args[2];
    char* newMovie1Name;
    char* newMovie2Name;
    char* newMovieName;

    if(argc != 5 && argc != 4){
        printInstruction();
        return 1;
    }

    if(argc == 5){
        newMovie1Name = args[3];
        newMovie2Name = args[4];
    } else if(argc == 4){
        newMovieName = args[3];
    }

    try{

        Movie* movie1 = new Movie(movie1Name);
        Movie* movie2 = new Movie(movie2Name);

        std::cout << "Movies loaded...\n1st movie frames no: " << movie1->getFramesNo() << "\n2nd movie frames no: " << movie2->getFramesNo() << "\n";

        int shift = MovieRegistrator::countOptimalShift(movie1, movie2);

        std::cout << "Proposed optimal shift: " << shift << " frames.\n";

        int length = MovieRegistrator::countIntersectionSize(movie1, movie2, shift);

        std::cout << "Length of new movies: " << length << " frames.\n";

        Movie* newMovie1 = MovieRegistrator::trimMovie(movie1, (shift > 0 ? shift : 0), length);
        Movie* newMovie2 = MovieRegistrator::trimMovie(movie2, (shift > 0 ? 0 : -shift), length);

        std::cout << "New movies created, waiting for saving...\n";

        if(argc == 5){
            newMovie1->save(newMovie1Name);
            newMovie2->save(newMovie2Name);

            std::cout << "Your movies were registered.\nResult saved in files:\n" << newMovie1Name << std::endl << newMovie2Name;
        }else if(argc == 4){
            Movie* newMovie = MovieRegistrator::glueMovies(newMovie1, newMovie2);
            newMovie->save(newMovieName);

            std::cout << "Your movie was registered.\nResult saved in file:\n" << newMovieName << std::endl;
        }
    } catch(const char* e){
        std::cout << "Exception occured: " << e << "\n";
        return 1;
    }

    return 0;
}
