/**
 * @file main.cpp
 * @date Spring 2012
 * @author Sean Massung 
 */

#include <algorithm>
#include <iostream>
#include <vector>

#include "png.h"
#include "collage.h"

#define NUM_COLLAGE_FILES 12

using std::vector;
using std::cout;
using std::endl;

/**
 * Turns a string green!
 * @param str - the string to change
 * @return the changed string
 */
inline string makeGreen(string str)
{
    return "\033[1;32m" + str + "\033[0m";
}

/**
 * Turns a string red to indicate you done wrong
 * @param str - the string to change
 * @return the angry string
 */
inline string makeRed(string str)
{
    return "\033[1;31m" + str + "\033[0m";
}

/**
 * Initializes the vector of PNGs for the collage constructor.
 * @return - a vector of PNGs representing layers in the collage
 */
vector<PNG> setupImages()
{
    vector<PNG> layers;
    string filenames[NUM_COLLAGE_FILES] = { "01_8182x4096.png", "02_5000x3750.png",
        "03_2560x1680.png", "04_1920x1200.png", "05_1680x1050.png",
        "06_1440x900.png", "07_1280x1024.png", "08_1024x768.png",
        "09_600x400.png", "10_300x200.png", "11_150x100.png", "12_50x50.png" };
    for(int i = 0; i < NUM_COLLAGE_FILES; ++i)
    {
        cout << "  - loading image " << i << endl;
        PNG png;
        png.readFromFile("images/" + filenames[i]);
        layers.push_back(png);
    }
    return layers;
}

/**
 * Initializes the vector of Points for the collage constructor.
 * @return - a vector of Points where each image will be relative in the collage
 */
vector<Point> setupPoints()
{
    int coords[NUM_COLLAGE_FILES][2] = { {0, 0}, {100, 100}, {200, 200}, {300, 500}, {800, 1000}, {0, 2000},
        {3000, 1000}, {4000, 300}, {300, 700}, {700, 300}, {0, 0}, {8000, 4000} };
    vector<Point> points;
    for(int i = 0; i < NUM_COLLAGE_FILES; ++i)
    {
        Point p(coords[i][0], coords[i][1]);
        points.push_back(p);
    }
    return points;
}

/**
 * Tests the collage by coordinates.
 */
void testCollage()
{
    cout << "Testing collage:" << endl;
    vector<PNG> layers = setupImages();
    vector<Point> coords = setupPoints();
    Collage collage(layers, coords);

    PNG* result = collage.draw();

    cout << "  - saving image" << endl;
    result->writeToFile("collage.png");    

    cout << "Checking correctness: ";
    bool correct = collage.checkCorrectness(*result);
    cout << (correct ? makeGreen("PASS") : makeRed("FAIL") + " (the images are different)") << endl;
    delete result;
}

/**
 * Entry point!
 */
int main()
{
    testCollage();
    return 0;
}
