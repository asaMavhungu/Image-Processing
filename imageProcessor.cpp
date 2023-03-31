#include "imageProcessor.h"
#include "connectedComponent.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <queue>

using namespace std;

void MVHASA001::PGMimageProcessor::readImage(string filename)
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

    // Set background and forground
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
			// set dummy black and white
			// will use real colors when doing flood fill
            if (pixels[i][j] > 128)
                pixels[i][j] = 254;
            else
				pixels[i][j] = 1;
        }
    }


	this->comment = comment;
	this->source = std::move(pixels); // move the pixel data to the class instance
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

// Check if the given row and column are within bounds
bool isSafe(int row, int col, int numRows, int numCols) 
{
    return (row >= 0 && row < numRows && col >= 0 && col < numCols);
}

int MVHASA001::PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize)
{
	using namespace std;
	return 0;

	using namespace std;
    int numRows = this->height;
    int numCols = this->width;
    int numComponents = 0;
    vector<vector<bool>> visited(numRows, vector<bool>(numCols, false));
    queue<pair<int, int>> q;

	
    for (int i = 0; i < numRows; i++) 
	{
        for (int j = 0; j < numCols; j++) 
		{

            if (!visited[i][j]) {
                q.push(make_pair(i, j));
                visited[i][j] = true;
                numComponents++;
				int size = 0;

                // Start new connected component
                while (!q.empty()) 
				{
                    pair<int, int> p = q.front();
                    q.pop();
                    int row = p.first;
                    int col = p.second;

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
					cout << "did not make component " << size << endl;
					--numComponents; 
				}
				else cout << "made component " << size << endl; 
				cout << "queue empty" << endl;
            }
        }
    }

    return numComponents;
}

bool MVHASA001::PGMimageProcessor::writeComponents(const std::string & outFileName)
{
	std::ostringstream oss;
	std::ofstream file(outFileName, std::ios::binary);
	file << "P5" << std::endl;
    file << this->width << " " << this->height << std::endl;
    file << "255" << std::endl;


	for (int y = 0; y < this->height; y++) 
	{
		file.write(reinterpret_cast<const char*>(this->source[y].data()), this->width); // invalid type conversionC/C++(171)
	}

}