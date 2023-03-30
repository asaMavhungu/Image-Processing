#include "imageProcessor.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <queue>

using namespace std;

void MVHASA001::PGMimageProcessor::readImage(std::string filename)
{
	std::ifstream in(filename, std::ios::binary);

	std::string format, commentBuffer, comment, line;
	int width = 0, height = 0, max_value = 0;

	// Read the first line to get the format
	std::getline(in, format);

	// Read any comment lines (starting with #)
	while (std::getline(in, commentBuffer)) 
	{
		if (commentBuffer[0] != '#') 
		{
			break;
		}
		comment = comment + commentBuffer;
	}

	// The last line that doesn't have '#' will be saved to comment
	std::istringstream iss(commentBuffer);
	iss >> width >> height;


	std::getline(in, line);
	std::istringstream iss2(line);
	iss2 >> max_value;

	// Remove whitespace
	in >> std::ws;

	// Allocate memory pixels
	unsigned char* buffer = new unsigned char[width * height];

	// Read the pixels into the buffer
	// Convert fron unsigned char to char to avoid type mismatch
	// because read() expects a char* not 'unsigned char*'
	in.read(reinterpret_cast<char*>(buffer), width * height);

	this->comment = comment;
	this->source = buffer;
	this->height = height;
	this->width = width;
	this->sourceSize = width * height;
	in.close();
}


void MVHASA001::PGMimageProcessor::process(vector<vector<unsigned char>> &image, int threshold,int width, int height)
{
	int row = 0;
	int col = 0;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			image[y][x] = (image[y][x] > threshold) ? 255 : 0;
		}

	}

}
