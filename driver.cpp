#include "imageProcessor.h"
#include <iostream>
#include <cstring>


int main(int argc, char* argv[])
{
	using namespace MVHASA001;


	int minSize = 3;
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
			minSize = std::stoi(argv[i+1]);
			++i;
			maxSize = std::stoi(argv[i+2]);
			++i;
		}
		if ( strcmp( argv[i], "-t") == 0)
		{
			threshold = std::stoi(argv[i+1]);
			i++;
		}
		if ( strcmp( argv[i], "-p") == 0)
		{
			printOut = true;
			i++;
		}
		if ( strcmp( argv[i], "-w") == 0)
		{
			writeOut = true;
			outFileName = argv[i+1];
			i++;
		}
	}



	//std::string inFilename = "chess.pgm";


	//PGMimageProcessor asa;
	//std::string filename3 = "chess.pgm";

	//asa.extractComponents(127, 3);
	//int maxSize = asa.getSourceSize();

	std::cout << asa.extractComponents(threshold, minSize) << " ------\n";
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

	std::cout << "Num: " << asa.getComponentCount() << endl;

	std::cout << minSize << " MIN "<< std::endl
		<< maxSize << " MAX" << std::endl
		<< threshold << " THRESH" << std::endl
		<< printOut << " OUT: " << inFilename << " NAME" << std::endl
		<< writeOut << " WRITE: " << asa.getLargestSize() << std::endl;
	


	//177/178 for chess


	std:: cout << "==========" << endl;
	asa.writeComponents("sample_out.pgm");
	std:: cout << asa.getLargestSize()<< endl;
	std:: cout << asa.getSmallestSize() << endl;
	std::cout << "Num1: " << asa.getComponentCount() << endl;

	asa.filterComponentsBySize(5000, 7500);
	std:: cout << "==========" << endl;
	asa.writeComponents("sample_fileter_out.pgm");

	std:: cout << asa.getLargestSize()<< endl;
	std:: cout << asa.getSmallestSize() << endl;
	std::cout << "Num2: " << asa.getComponentCount() << endl;

	for (int i = 0; i < asa.getComponentCount(); ++i)
	{
		std::cout << asa.getComponent(i).getBounds() << "das ";
		asa.printComponentData(asa.getComponent(i));
		
	}
	
	//std::multiset<std::shared_ptr<ConnectedComponent>, compareComponents> bee = asa.getComponents();
	//auto it = bee.begin();
	//asa.printComponentData(*(*it));
	


}