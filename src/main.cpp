#include "ppm.hpp"
#include <iostream>

void test1(std::string filename) {
	//PPM myPPM("./myppm_p3.ppm");
	PPM myPPM(filename);
	myPPM.lighten();
	myPPM.saveP3("./p3_lightened.ppm");
	myPPM.saveP6("./p6_lightened.ppm");
}

void test2(std::string filename) {
	PPM myPPM(filename);
	myPPM.darken();
	myPPM.saveP3("./p3_darkened.ppm");
	myPPM.saveP6("./p6_darkened.ppm");
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Cannot run program.\n"
			"Usage: . / ppm <input_file> <output_file>"
			"\n  input_file - Path to input PPM file"
			"\n  output_file - Path to output PPM file"
	<< std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "argument count is " << argc << std::endl;
	std::cout << "argument values are " << argv[0] << " and " << argv[1] << std::endl;



	test1(argv[1]);
	test2(argv[1]);

	// size of the class is 
	std::cout << "Size of PPM class is " << sizeof(PPM) << std::endl;
	

	return EXIT_SUCCESS;
}


Refactor PPM class for uint8_t pixel storage to make efficient by saving memory
- Added  <cstdint >   header for fixed - width types.
- Changed pixel data type from  int  to  uint8_t .
- Updated  mPixels  to use  std::vector<uint8_t> .
- Modified constructor and test functions to accept filename arguments.
- Ensured pixel values are correctly formatted as integers in  savePPM .