/**
 * @file collage.cpp
 */

#include "collage.h"

/**
 * Constructor
 * @param layers - PNG images that will be used in the collage
 * @param coords - where each image is relative in the entire collage's coordinate system
 */
Collage::Collage(const vector<PNG> & layers, const vector<Point> & coords)
{
	this->layers = layers;
	this->coords = coords;
	width = getWidth(coords, layers);
	height = getHeight(coords, layers);
}

/**
 * Calculate which image each (x,y) coordinate belongs to, then draw it.
 * @return pointer to the collage
 */
PNG *Collage::draw()
{
	PNG* result = new PNG(width, height);
	// loop over the collage image
	for(int i = 0; i < width; ++i)
	{
		for(int j = 0; j < height; ++j)
		{
			// find which image the current (i, j) pixel will belong to (if any)
			for(size_t layer = layers.size(); layer >= 0; --layer)
			{
				// get offset
				int offsetW = coords[layer].x;
				int offsetH = coords[layer].y;
				int layerW  = layers[layer].width();
				int layerH  = layers[layer].height();
				int newI = i - offsetW;
				int newJ = j - offsetH;
				if(inBounds(newI, newJ, layerW, layerH))
				{
					// we found the highest layer; this pixel will be changed
					*(*result)(i, j) = *(layers[layer](newI, newJ));
					// we don't need to look anymore
					break;
				}
			}
		}
	}
	return result;
}

/**
 * Returns whether x is in the range [0, xBound) and y is in the range [0, yBound)
 * @param x
 * @param y
 * @param xBound - the upper bound (exclusive) that x may be
 * @param yBound - the upper bound (exclusive) that y may be
 * @return - whether the given coordinates are in range
 */
bool Collage::inBounds(int x, int y, int xBound, int yBound)
{
	bool xValid = (x >= 0 && x < xBound);
	bool yValid = (y >= 0 && y < yBound);
	return xValid && yValid;
}

/**
 * Returns the width that the collage will be
 * @param coords - a vector of coordinates where each image will be
 *				   relative to the entire collage
 * @param layers - a vector of PNGs that will be used as layers in the collage
 * @return - the maximum width needed in the image containing all the layers
 */
int Collage::getWidth(const vector<Point> & coords, const vector<PNG> & layers)
{
	int maxWidth = 0;
	for(size_t i = 0; i < layers.size(); ++i)
	{
		int currentWidth = coords[i].x + layers[i].width();
		if(currentWidth > maxWidth)
		{
			maxWidth = currentWidth;
		}
	}
	return maxWidth;
}

/**
 * Returns the height that the collage will be
 * @param coords - a vector of coordinates where each image will be
 *				   relative to the entire collage
 * @param layers - a vector of PNGs that will be used as layers in the collage
 * @return - the maximum height needed in the image containing all the layers
 */
int Collage::getHeight(const vector<Point> & coords, const vector<PNG> & layers)
{
	int maxHeight = 0;
	for(size_t i = 0; i < layers.size(); ++i)
	{
		int currentHeight = coords[i].y + layers[i].height();
		if(currentHeight > maxHeight)
		{
			maxHeight = currentHeight;
		}
	}
	return maxHeight;
}

/**
 * Makes sure that the collage.png matches soln_collage.png
 * @param image - the image to test
 * @return - whether it matches soln_collage.png
 */
bool Collage::checkCorrectness(const PNG & image)
{
	PNG solution;
	solution.readFromFile("soln_collage.png");
	return solution == image;
}

