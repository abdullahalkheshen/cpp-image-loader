#include "ppm.hpp"
#include <iostream>

void test1(std::string filename) {
	PPM myPPM("./myppm_p3.ppm");
	myPPM.lighten();
	myPPM.savePPM("./myppm_p3_lightened.ppm");
}

void test2(std::string filename) {
	PPM myPPM("./myppm_p3.ppm");
	myPPM.darken();
	myPPM.savePPM("./myppm_p3_darkened.ppm");
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
	test2(argv[2]);

	return EXIT_SUCCESS;
}