#include "image.hpp"

void Image::flipleft ()
{
    for(int i = 0; i < PNG::width()/2; i++)
    {
        for(int j = 0; j < PNG::height(); j++)
        {
            RGBAPixel * b =  PNG::operator()(PNG::width()-i-1,j);
            RGBAPixel * a =  PNG::operator()(i,j);
            RGBAPixel temp = *a;
            *a = *b;
            *b = temp;
//            std::cout << "swapping pixels: "<< PNG::width()-i << "," << j << " and " << i << "," << j << std::endl;
        }
    }
}
void Image::adjustbrightness (int r, int g, int b)
{

    for(int i = 0; i < PNG::width(); i++)
    {
        for(int j = 0; j < PNG::height(); j++)
        {
            RGBAPixel * pxPtr = PNG::operator()(i,j);

            if(pxPtr->red + r < 0)
                pxPtr->red = 0;
            else if(pxPtr->red + r > 255)
                pxPtr->red = 255;
            else
                pxPtr->red += r;

            if(pxPtr->green + g < 0)
                pxPtr->green = 0;
            else if(pxPtr->green + g > 255)
                pxPtr->green = 255;
            else
                pxPtr->green += g;

            if(pxPtr->blue + b < 0)
                pxPtr->blue = 0;
            else if(pxPtr->blue + b > 255)
                pxPtr->blue = 255;
            else
                pxPtr->blue += b;

            // if(pxPtr->blue != (debug(i,j))->blue)
            //     std::cout<<"blue error at pixel "<<i<<"x"<<j<<std::endl;
            // if(pxPtr->red != (debug(i,j))->red)
            //     std::cout<<"red error at pixel "<<i<<"x"<<j<<std::endl;
            
        }
    }
}
void Image::invertcolors ()
{
    for(int i = 0; i < PNG::width(); i++)
    {
        for(int j = 0; j < PNG::height(); j++)
        {
            RGBAPixel * pxPtr = PNG::operator()(i,j);
            pxPtr->green = 255-pxPtr->green;
            pxPtr->red = 255-pxPtr->red;
            pxPtr->blue = 255-pxPtr->blue;
        }
    }
            
            
}

