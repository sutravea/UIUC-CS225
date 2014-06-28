#include "rgbapixel.h"
#include <iostream>
#include "png.h"

using namespace std;

int main() {
    PNG in = PNG ("in.png");
    int width = in.width();
    int height = in.height();

    PNG out = PNG (width, height);
        
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++)	{
            *out(width-1-i,height-1-j) = *in(i,j);
	}
    }
  
    out.writeToFile("out.png");
}



