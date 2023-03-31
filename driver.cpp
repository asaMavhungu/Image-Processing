#include "imageProcessor.h"
#include <iostream>
#include <limits>



int main()
{
	using namespace MVHASA001;
	using namespace std;
	
	PGMimageProcessor asa;
	std::string filename3 = "sample_1280×853.pgm";

	asa.setImage(filename3);

	cout << asa.extractComponents(128, 30000) << " ------\n";

	asa.writeComponents("sample_out.pgm");


}