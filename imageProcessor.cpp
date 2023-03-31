#include "imageProcessor.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <queue>

using namespace std;

namespace MVHASA001
{

	void PGMimageProcessor::setImage(string filename)
	{
		this->sourceName = filename;
	}

	void PGMimageProcessor::readImage(string filename, unsigned char threshold)
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

		// Read pixel data to 2D vector
		std::vector<std::vector<unsigned char>> pixels(height, std::vector<unsigned char>(width));
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				in.read((char*)&pixels[i][j], 1);
			}
		}
		// TODO make sure sont need original data
		// this->source = pixels; // save original sorce

		// Set background and forground
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				// set dummy black and white
				// will use real colors when doing flood fill
				if (pixels[i][j] > threshold)
					pixels[i][j] = 255;
				else
					pixels[i][j] = 0;
			}
		}


		this->comment = comment;
		this->source = std::move(pixels); // move the pixel data to the class instance
		this->height = height;
		this->width = width;
		this->sourceSize = width * height;
		in.close();
	}


	void PGMimageProcessor::process(vector<vector<unsigned char>> &image, int threshold,int width, int height)
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

	// Check if the given row and column are within bounds
	bool isSafe(int row, int col, int numRows, int numCols) 
	{
		return (row >= 0 && row < numRows && col >= 0 && col < numCols);
	}

	void floodFill(std::vector<std::vector<unsigned char>> & source, int row, int col, int target, int replacement)
	{
		// If the current cell is already the replacement value or is outside the bounds of the matrix, return
		if (row < 0 || row >= source.size() || col < 0 || col >= source[0].size() || source[row][col] != target) 
		{
			std::cout << row << " " << col << " " << target << std::endl;
			return;
		}

		// Change color
		source[row][col] = replacement;
		std::cout << row << col << std::endl;

		// Recursively fill the neighboring cells
		floodFill(source, row + 1, col, target, replacement);
		floodFill(source, row - 1, col, target, replacement);
		floodFill(source, row, col + 1, target, replacement);
		floodFill(source, row, col - 1, target, replacement);
	}

	int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize)
	{
		using namespace std;

		readImage(this->sourceName, threshold);

		int numRows = this->height;
		int numCols = this->width;
		int numComponents = 0;
		vector<vector<bool>> visited(numRows, vector<bool>(numCols, false));
		queue<pair<int, int>> q;

		
		for (int i = 0; i < numRows; i++) 
		{	
			for (int j = 0; j < numCols; j++) 
			{
				if(this->source[i][j] < threshold)
					continue;
				if (!visited[i][j]) {
					q.push(make_pair(i, j));
					visited[i][j] = true;
					numComponents++;
					int size = 0;

					// Start new connected component
					// TODO make array to hold the pixels(x, y) changed to store in component
					ConnectedComponent *comp = new ConnectedComponent(numComponents);
					//cout << comp->getSize() << size << endl;
					while (!q.empty()) 
					{
						pair<int, int> p = q.front();
						q.pop();
						int row = p.first;
						int col = p.second;

						std::pair<int,int> p1 = std::make_pair(i,j);
						*comp += p1;

						++size;


						// Check neighbor pixels
						if (isSafe(row-1, col, numRows, numCols) && !visited[row-1][col]
							&& this->source[row-1][col] == this->source[row][col]) 
						{
							q.push(make_pair(row-1, col));
							visited[row-1][col] = true;
							//cout << "queued" << row-1 << col<< endl;
						}
						if (isSafe(row+1, col, numRows, numCols) && !visited[row+1][col]
							&& this->source[row+1][col] == this->source[row][col]) 
						{
							q.push(make_pair(row+1, col));
							visited[row+1][col] = true;
							//cout << "queued" << row+1 << col<< endl;
						}
						if (isSafe(row, col-1, numRows, numCols) && !visited[row][col-1]
							&& this->source[row][col-1] == this->source[row][col]) 
						{
							q.push(make_pair(row, col-1));
							visited[row][col-1] = true;
							//cout << "queued" << row << col-1<< endl;
						}
						if (isSafe(row, col+1, numRows, numCols) && !visited[row][col+1]
							&& this->source[row][col+1] == this->source[row][col]) 
						{
							q.push(make_pair(row, col+1));
							visited[row][col+1] = true;
							//cout << "queued" << row <<col+1<< endl;
						}
					}
					if (size <= minValidSize) 
					{
						//cout << "did not make component " << size << endl;
						// TODO make and not make components
						floodFill(this->source, i, j, 255, 0);
						delete comp;
						--numComponents; 
					}
					else 
					{
						comp->setSize(size);
						this->addComponent(*comp);
						delete comp;
						//cout << this->components[0] <<" ONE\n";
					}
					//cout << "queue empty" << endl;
				}
			}
		}
		
		
		return numComponents;
	}

	bool PGMimageProcessor::writeComponents(const std::string & outFileName)
	{
		std::ostringstream oss;
		std::ofstream file(outFileName, std::ios::binary);
		file << "P5" << std::endl;
		file << this->width << " " << this->height << std::endl;
		file << "255" << std::endl;


		for (int y = 0; y < this->height; y++) 
		{
			file.write(reinterpret_cast<const char*>(this->source[y].data()), this->width);
		}

		return true;

	}

	


}

