#include "imageProcessor.h"
#include "connectedComponent.h"
#include <iostream>


int main()
{
	using namespace MVHASA001;
	using namespace std;
	
	PGMimageProcessor asa;
	std::string filename3 = "sample_1280×853.pgm";

	asa.setImage(filename3);
	//asa.readImage(filename3);
	cout << asa.extractComponents(200, 12) << " ------";
	asa.writeComponents("sample_out.pgm");


}