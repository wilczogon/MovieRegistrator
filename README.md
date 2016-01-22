# MovieRegistrator

## What it is?

MovieRegistrator is simple tool for registering and trimming videos of the same scene in nearly the same time.
For example, when you try to record two videos to test depth detecting algorithm, it can be problem to have movies from two cameras with the same number of frames and with recorded scene in the same time.
MovieRegistrator help with this.

## Important info to run

It is CodeBlocks project - the easiest way to compile it is to import project to CodeBlocks.
Dlls added to main folder should be available in run location when you will be using MovieRegistrator.

## Format of arguments

There are two ways of running it:

1) MovieRegistrator [path to 1st movie] [path to second movie] [result 1st path] [result 2nd]
Here the result will be two movies with the same number of frames and registered to show the same scene.

2) MovieRegistrator [path to 1st movie] [path to second movie] [result path]
Here the result will be one movie, which will be glued from result movies from 1)
