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
void Image::adjustbrightness (int r, int g, int b){

}
void Image::invertcolors (){}

