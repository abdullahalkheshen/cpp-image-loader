#include "pixel.hpp"
#include <string>
#include <vector>

class PPM {
public:
	// Constructor
    PPM(std::string filename);
	// Destructor
	~PPM();

	// Member functions
	void savePPM(std::string out_file_name);
	void lighten();
	void darken();

private:

	std::vector<pixel> mPixels;
	//std::array<pixel*, int m> mPixelArray;
	int mWidth, mHeight, mMaxRange;

};