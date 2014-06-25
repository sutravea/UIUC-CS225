#include <cstdlib>
#include "png.h"
#include <iostream>
// sets up the output image
PNG * setupOutput(int w, int h);
using namespace std;
// Returns my favorite color
RGBAPixel * myFavoriteColor(int intensity);

int main()
{
    // Load in.png
    PNG origPNG = PNG("in.png");
    PNG * original = &origPNG;

//    original->readFromFile("in.png");

    int width  = original->width();

    int height = original->height();

    // Create out.png
    PNG * output = setupOutput(width, height);	

    // Loud our favorite color to color the outline
    RGBAPixel * myPixel = myFavoriteColor(192);

    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
    for (int y = 1; 0 < y && y < height; y++)
    {        
        for (int x = 1; 0 < x && x < width; x++)
        {
            // Calculate the pixel difference
//            RGBAPixel * prev = (*original)(x-1, y-1);
//            RGBAPixel * curr = (*original)(x  , y  );
            // int diff = abs(curr->red   - prev->red  ) +
            //     abs(curr->green - prev->green) +
            //             abs(curr->blue  - prev->blue );

            // // If the pixel is an edge pixel,
            // // color the output pixel with my favorite color
            // RGBAPixel * currOutPixel = (*output)(x,y);
            // if (diff > 100)
            //     currOutPixel = myPixel;
        }
    }
    cout << "reached line "<< __LINE__<<endl;
    // Save the output file
    output->writeToFile("out.png");
    cout << "reached line "<< __LINE__<<endl;    
    // Clean up memory
    delete myPixel;
    cout << "reached line "<< __LINE__<<endl;    
    delete output;
    cout << "reached line "<< __LINE__<<endl;    
    delete original;
    cout << "reached line "<< __LINE__<<endl;    
    return 0;
}


// sets up the output image
PNG * setupOutput(int w, int h)
{
    PNG * image = new PNG(w, h);
    return image;
}


// Returns my favorite color
RGBAPixel * myFavoriteColor(int intensity)
{
    RGBAPixel color;
    color.red   = 0;
    color.green = intensity/2;
    color.blue  = intensity;
    return &color;
}
