#pragma once
#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include <iostream>
#include "system/Log.h"
#include <sstream>


class Texture 
{
public:

	Texture();
	// Loads from file while declaring

	Texture(const char* path, bool alpha = false);
	~Texture();
	// Loads an image file
	void Load(const char* path, bool png=false);
	// Readies the texture to be used
	void Bind(unsigned int slot =0);
	// Binds 0 to slot, and sets boundSlot to -1
	void Unbind();

	int GetBoundSlot() { return boundSlot; }

	// Width and height data for image and number of color channels
	int width, height, channels;
private:
	// Opengl id for texture
	unsigned int texID;
	int boundSlot;
};

struct SubTexture {

	// Default constructor makes tex coordinates whole texture
	SubTexture() :
	xPix(0), yPix(0), pixWidth(0), pixHeight(0), 
	xCoord(0.0f), yCoord(0.0f), coordWidth(1.0f), coordHeight(1.0f){}

	SubTexture(Texture* tex, int xOffset, int yOffset, int width, int height) :
		xPix(xOffset), yPix(yOffset), pixWidth(width), pixHeight(height) {

		CalculateCoordinates(tex->width, tex->height);
	}

	void SetValues(Texture* tex, int xOffset, int yOffset, int width, int height) {
		xPix = xOffset;
		yPix = yOffset;
		pixWidth = width;
		pixHeight = height;
		CalculateCoordinates(tex->width, tex->height);
	}
	// Pixel x and y offset with size
	int xPix, yPix;
	int pixWidth, pixHeight;

	// For texture coordinates
	float xCoord, yCoord;
	float coordWidth, coordHeight;

	void CalculateCoordinates(int tWidth, int tHeight) {
		xCoord = (float)xPix / (float)tWidth;
		yCoord = (float)yPix / (float)tHeight;
		coordWidth = (float)pixWidth / (float)tWidth;
		coordHeight = (float)pixHeight / (float)tHeight;
	}
};
