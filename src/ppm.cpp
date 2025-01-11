
// Serves as the implementation of the PPM class our interface in ppm.hpp.

#include "ppm.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

PPM::PPM(std::string filename) {
	std::cout << "PPM::PPM()\n";

	std::ifstream input_file;
	input_file.open(filename);

	bool foundP3 = false;
	bool foundDimensions = false;
	bool foundRange = false;
	bool readingPixels = false;
	
	//std::cout << typeid(input_file).name() << std::endl;

	if (input_file.is_open()) {
		std::cout << filename << " opened successfully\n";
		std::string line;
		while (std::getline(input_file, line)) {
			std::cout << line << std::endl;
			std::stringstream stream(line);
			std::string chunk_of_line;
			while (stream >> chunk_of_line) {
				if (chunk_of_line[0] == '#') {
					std::cout << line << std::endl;
					break;
				}
				else if (!foundP3) {
					if (chunk_of_line == "P3") {
						foundP3 = true;
						std::cout << "Found P3\n";
					}
					else {
						std::cout << "Error: P3 not found\n";
						break;
					}
				}
				else if (!foundDimensions) {
					mWidth = std::stoi(chunk_of_line);
					stream >> chunk_of_line;
					mHeight = std::stoi(chunk_of_line);
					std::cout << "Width: " << mWidth << " Height: " << mHeight << std::endl;
					foundDimensions = true;
				}
				else if (!foundRange) {
					mMaxRange = std::stoi(chunk_of_line);
					std::cout << "Max color value: " << mMaxRange << std::endl;
					foundRange = true;
				}
				else if (!readingPixels) {
					// Read the pixels
					readingPixels = true;
					std::cout << "Reading pixels\n";
				}
				else {
					// Read the pixels
					std::cout << "Reading pixels\n";
				}
			}
		}
	}
}

PPM::~PPM() {
	std::cout << "PPM::~PPM()\n";
}

void PPM::savePPM(std::string out_file_name) {
	std::cout << "PPM::savePPM()\n";
}

void PPM::lighten() {
	std::cout << "PPM::lighten()\n";
}

void PPM::darken() {
	std::cout << "PPM::darken()\n";
}