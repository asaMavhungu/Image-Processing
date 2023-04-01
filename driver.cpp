#include "imageProcessor.h"
#include <iostream>
#include <limits>
#include <cstring>
#include <limits>



int main(int argc, char* argv[])
{
	using namespace MVHASA001;


	int minSize = 3;
	int maxSize = 0;
	int threshold = 128;

	bool printOut = false;
	bool writeOut = false;

	std::string inFilename = argv[argc - 1];
	std::string outFileName = "";

	PGMimageProcessor asa;

	asa.setImage(inFilename);

	

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
			printOut = true;
			outFileName = argv[i+1];
			i++;
		}
	}



	//std::string inFilename = "chess.pgm";


	//PGMimageProcessor asa;
	//std::string filename3 = "chess.pgm";

	asa.setImage(inFilename);
	//asa.extractComponents(127, 3);
	//int maxSize = asa.getSourceSize();


	std::cout << minSize << " MIN "<< std::endl
		<< maxSize << " MAX" << std::endl
		<< threshold << " THRESH" << std::endl
		<< printOut << " OUT: " << inFilename << " NAME" << std::endl
		<< writeOut << " WRITE: " << outFileName << std::endl;
	


	//177/178 for chess
	std::cout << asa.extractComponents(threshold, minSize) << " ------\n";
	//cout << asa.getComponents()[0] <<" ONE\n";
	//cout << asa.getComponents()[2] <<" ONE\n";

	std:: cout << "==========" << endl;
	asa.writeComponents("sample_out2.pgm");
	std::cout << "Num: " << asa.getComponentCount() << endl;

	asa.filterComponentsBySize(5000, 7500);
	std:: cout << "==========" << endl;
	asa.writeComponents("filtered_out434.pgm");

	std::cout << "Num: " << asa.getComponentCount() << endl;
	
	//std::multiset<std::shared_ptr<ConnectedComponent>, compareComponents> bee = asa.getComponents();
	//auto it = bee.begin();
	//asa.printComponentData(*(*it));
	


}