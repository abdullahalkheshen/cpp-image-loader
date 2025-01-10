// Serves as the implementation of the PPM class our interface in ppm.hpp.

#include <iostream>
#include "ppm.hpp"

PPM::PPM(std::string out_file_name) {
	std::cout << "PPM::PPM()\n";
}

PPM::~PPM() {
	std::cout << "PPM::~PPM()\n";
}

void PPM::savePPM(std::string out_file_name) {
	std::cout << "PPM::savePPM()\n";
}

void PPM::lighten() {};
void PPM::darken() {};