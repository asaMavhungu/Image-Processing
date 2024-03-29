#include "imageProcessor.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <queue>
#include <algorithm>
#include <stack>

using namespace std;

namespace MVHASA001
{

	PGMimageProcessor::PGMimageProcessor(): width(0), height(0), id(nullptr), sourceSize(0) 
	{}

	PGMimageProcessor::PGMimageProcessor(std::string srcName) : width(0), height(0), id(nullptr), sourceName(srcName), sourceSize(0), comment("") {}

	PGMimageProcessor::~PGMimageProcessor() = default;

	PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor& other)
	{
		this->width = other.width;
    	this->height = other.height;
		this->sourceName = other.sourceName;
    	this->source = other.source;
		this->components = other.components;
		this->sourceSize = other.sourceSize;
		this->comment = other.comment;
	}

	PGMimageProcessor::PGMimageProcessor(PGMimageProcessor&& other)
	{
		this->width = other.width;
    	this->height = other.height;
		this->sourceName = std::move(other.sourceName);
    	this->source = std::move(other.source);
		this->components = std::move(other.components);
		this->sourceSize = other.sourceSize;
		this->comment = std::move(other.comment);

		other.width = 0;
		other.height = 0;
		other.sourceSize = 0;
		other.sourceName = "";
		other.comment = "";
	}

	PGMimageProcessor& PGMimageProcessor::operator=(PGMimageProcessor& other)
	{
		if (this != &other)
		{
			this->width = other.width;
			this->height = other.height;
			this->sourceName = other.sourceName;
			this->source = other.source;
			this->components = other.components;
			this->sourceSize = other.sourceSize;
			this->comment = other.comment;

		}
		return *this;
	}
	
	PGMimageProcessor& PGMimageProcessor::operator=(PGMimageProcessor&& other)
	{
		if (this != &other)
		{
			this->width = other.width;
			this->height = other.height;
			this->sourceName = std::move(other.sourceName);
			this->source = std::move(other.source);
			this->components = std::move(other.components);
			this->sourceSize = other.sourceSize;
			this->comment = std::move(other.comment);

			other.width = 0;
			other.height = 0;
			other.sourceSize = 0;
			other.sourceName = "";
			other.comment = "";

		}
		return *this;
	}

	int PGMimageProcessor::getSourceSize() const
	{
		return this->sourceSize;
	}

	std::string PGMimageProcessor::getSourceName() const
	{
		return this->sourceName;
	}

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

	// Check if the given row and column are within bounds
	bool isSafe(int row, int col, int numRows, int numCols) 
	{
		return (row >= 0 && row < numRows && col >= 0 && col < numCols);
	}

	void PGMimageProcessor::floodFill(int row, int col, int target, int replacement)
	{

		int numRows = this->height;
		int numCols = this->width;
		int numComponents = 0;
		vector<vector<bool>> visited(numRows, vector<bool>(numCols, false));
		queue<pair<int, int>> q;

		q.push(std::make_pair(row, col));

		while (!q.empty()) 
		{
			pair<int, int> p = q.front();
			q.pop();
			int row = p.first;
			int col = p.second;

			// check if cell is valid for painting
			if (row < 0 || row >= int(this->source.size()) || col < 0 || col >= int(this->source[0].size()) || this->source[row][col] != target)
			{
				continue;
			}

			// Change color
			source[row][col] = replacement;

			// Push neighbor cells to Q
			q.push(std::make_pair(row + 1, col));
			q.push(std::make_pair(row - 1, col));
			q.push(std::make_pair(row, col + 1));
			q.push(std::make_pair(row, col - 1));
		}

	}

	int PGMimageProcessor::calcBoundaries(const std::vector< std::pair<int,int> > & points)
	{	
		int bounds = std::count_if(points.begin(), points.end(), [this](const std::pair<int,int>& point) { return this->isBoundary(point); });
		return bounds;
	}

	bool PGMimageProcessor::isBoundary(const std::pair<int,int> & point) const
	{
		int row = point.first;
		int col = point.second;

		if (isSafe(row-1, col, height, width) && this->source[row-1][col] != this->source[row][col]) 
			return true;

		if (isSafe(row+1, col, height, width) && this->source[row+1][col] != this->source[row][col]) 
			return true;

		if (isSafe(row, col-1, height, width) && this->source[row][col-1] != this->source[row][col]) 
			return true;

		if (isSafe(row, col+1, height, width) && this->source[row][col+1] != this->source[row][col]) 
			return true;

		return false;
	}

	void PGMimageProcessor::addComponent(std::shared_ptr<ConnectedComponent> comp)
	{
		this->components.insert(comp);
		//std::cout << "added comp " << comp << std::endl;
	}

	const ConnectedComponent & PGMimageProcessor::getComponent(int index) const
	{
		if (index < 0 || index >= this->components.size()) 
		{
			// index out of bounds error
			throw std::out_of_range("Index out of bounds");
		}

		std::multiset<std::shared_ptr<ConnectedComponent>, compareComponents>::iterator it;

		it = std::next(this->components.begin(), index);

		return *(*it);
	}

	const std::multiset<std::shared_ptr<ConnectedComponent>, MVHASA001::compareComponents>& PGMimageProcessor::getComponents() const
	{
		return components;
	}

	int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize)
	{
		using namespace std;

		// clear set before re-extracting
		this->components.clear();
		if (this->sourceSize == 0)
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
					std::shared_ptr comp = std::make_shared<ConnectedComponent>(numComponents);
					//cout << comp->getSize() << size << endl;
					while (!q.empty()) 
					{
						pair<int, int> p = q.front();
						q.pop();
						int row = p.first;
						int col = p.second;

						std::pair<int,int> p1 = std::make_pair(row,col);
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
					if (size < minValidSize) 
					{
						//cout << "did not make component " << size << endl;
						// Paint out the now-invalid component
						floodFill(i, j, 255, 0);
						--numComponents; 
					}
					else 
					{
						comp->setSize(size);
						const std::vector< std::pair<int,int> > & points = comp->getPoints();
						int numBounds = calcBoundaries(points);
						comp->setBounds(numBounds);
						this->addComponent(comp);
					}
					//cout << "queue empty" << endl;
				}
			}
		}
		
		
		return numComponents;
	}

	int PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize)
	{

		/* vectors .begin() returns read-and-write iterators
		multiset return iterators to const elemets in set
		(modifying elements in set breaks ordering)
		Needed to change getPoint() to be const because of this
		*/
		std::multiset<std::shared_ptr<ConnectedComponent>, compareComponents>::iterator it;

		/* The set is already sorted.
		It is faster to remove elements from both ends instrad of 
		looping through the entire container
		*/

		it = this->components.begin();
		while(it != this->components.end())
		{
			if ((*it)->getSize() < minSize)
			{
				std::pair<int,int> p = (*it)->getPoint(); 
				int row = p.first;
				int col = p.second;
				// Paint out the now-invalid component
				floodFill(row, col, 255, 0);
				it = this->components.erase(it);
			}
			else
			{
				break;
			}

		}

		it = this->components.end();
		while(it != this->components.begin())
		{
			--it;
			if ((*it)->getSize() > maxSize)
			{
				std::pair<int,int> p = (*it)->getPoint(); 
				int row = p.first;
				int col = p.second;
				floodFill(row, col, 255, 0);
				it = this->components.erase(it);
			}
			else
			{
				break;
			}

		}
		return this->components.size();
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


	int PGMimageProcessor::getComponentCount(void) const
	{
		return this->components.size();
	}

	int PGMimageProcessor::getLargestSize(void) const
	{	
		// Uses overload '<' of connected component by default
		// std::multiset<ConnectedComponent, MVHASA001::compareComponents>::const_iterator it = std::max_element(this->components.begin(), this->components.end());

		std::multiset<std::shared_ptr<ConnectedComponent>, compareComponents>::const_reverse_iterator rit = components.rbegin();  // Get reverse iterator pointing to last element
		if (rit != components.rend()) 
		{
			ConnectedComponent* lastComp = rit->get();
			return lastComp->getSize();
		}

		return 0;
	}

	int PGMimageProcessor::getSmallestSize(void) const
	{
		// Uses overload '<' of connected component by default
		// std::multiset<ConnectedComponent, MVHASA001::compareComponents>::const_iterator it = std::min_element(this->components.begin(), this->components.end());

		std::multiset<std::shared_ptr<ConnectedComponent>, MVHASA001::compareComponents>::const_iterator it = std::min_element(this->components.begin(), this->components.end(), MVHASA001::compareComponents());
		
		if (it != components.end()) 
		{
			ConnectedComponent* lastComp = it->get();
			return lastComp->getSize();
		}

		return 0;

	}

	void PGMimageProcessor::printComponentData(const ConnectedComponent & theComponent) const
	{
		std::cout << theComponent << std::endl;
	}

	void PGMimageProcessor::printAllComponentData(const ConnectedComponent & theComponent) const
	{
		std::cout << theComponent << ", Bounds: " << theComponent.getBounds() << std::endl;
	}

	


}

