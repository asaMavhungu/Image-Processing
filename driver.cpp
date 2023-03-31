#include "imageProcessor.h"
#include <iostream>
#include <limits>



int main()
{
	using namespace MVHASA001;
	using namespace std;
	
	PGMimageProcessor asa;
	std::string filename3 = "chess.pgm";

	asa.setImage(filename3);
	// 177/178 for chess
	cout << asa.extractComponents(177, 60) << " ------\n";
	cout << asa.getComponents()[0] <<" ONE\n";
	cout << asa.getComponents()[2] <<" ONE\n";
	asa.writeComponents("sample_out.pgm");


}