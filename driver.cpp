#include "imageProcessor.h"
#include <iostream>
#include <cstring>
#include <sstream>

int main(int argc, char* argv[])
{
	using namespace MVHASA001;


	int minSize = 3;

	bool maxSet = false;
	int maxSize = 0;
	int threshold = 55;

	bool printOut = false;
	bool allInfo = false;
	bool writeOut = false;

	std::string inFilename = argv[argc - 1];
	std::string outFileName = "";

	PGMimageProcessor a(inFilename);

	

	for (int i = 1; i < argc - 1; ++i)
	{
		if ( strcmp( argv[i], "-s") == 0)
		{
			maxSet = true;
			minSize = std::stoi(argv[i+1]);
			++i;
			maxSize = std::stoi(argv[i+2]);
			++i;
		}
		if ( strcmp( argv[i], "-t") == 0)
		{
			threshold = std::stoi(argv[i+1]);
			++i;
		}
		if ( strcmp( argv[i], "-p") == 0)
		{
			printOut = true;
		}
		if ( strcmp( argv[i], "-b") == 0)
		{
			allInfo = true;
		}
		if ( strcmp( argv[i], "-w") == 0)
		{
			writeOut = true;
			outFileName = argv[i+1];
			++i;
		}
	}

	a.extractComponents(threshold, minSize);
	if (!maxSet)
		maxSize = a.getSourceSize();
	
	a.filterComponentsBySize(minSize, maxSize);
	if (printOut)
	{
		for (int i = 0; i < a.getComponentCount(); ++i)
		{
			a.printComponentData(a.getComponent(i));
		}
		std::cout << "Smallest size: " << a.getSmallestSize() << std::endl;
		std::cout << "Largest size: " << a.getLargestSize() << std::endl;
	}
	if (allInfo)
	{
		for (int i = 0; i < a.getComponentCount(); ++i)
		{
			a.printAllComponentData(a.getComponent(i));
		}
		std::cout << "Smallest size: " << a.getSmallestSize() << std::endl;
		std::cout << "Largest size: " << a.getLargestSize() << std::endl;
	}

	if (writeOut)
	{
		a.writeComponents(outFileName);
	}

	
}