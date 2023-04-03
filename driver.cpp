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
	bool writeOut = false;

	std::string inFilename = argv[argc - 1];
	std::string outFileName = "";

	PGMimageProcessor asa(inFilename);

	

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
		if ( strcmp( argv[i], "-w") == 0)
		{
			writeOut = true;
			outFileName = argv[i+1];
			++i;
		}
	}

	asa.extractComponents(threshold, minSize);
	if (!maxSet)
		maxSize = asa.getSourceSize();
	
	asa.filterComponentsBySize(minSize, maxSize);
	if (printOut)
	{
		for (int i = 0; i < asa.getComponentCount(); ++i)
		{
			asa.printComponentData(asa.getComponent(i));
		}
	}
	if (writeOut)
	{
		asa.writeComponents(outFileName);
	}

	
}