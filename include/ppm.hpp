#ifndef PPM_HPP
#define PPM_HPP

#include <string>
#include <vector>
#include <cstdint>

class PPM {
public:
	// Constructor that takes a PPM file name and reads its contents
	PPM(const std::string& filename);

	// Virtual destructor to allow for inheritance if needed
	virtual ~PPM();

	// Save the PPM data to a file
	void saveP3(const std::string& out_file_name) const;
	void saveP6(const std::string& out_file_name) const;

	// Image manipulation functions
	void lighten();
	void darken();

	// Utility functions
	void clear();
	bool isValid() const;

	// Getters
	int getWidth() const;
	int getHeight() const;
	int getMaxRange() const;
	const std::vector<uint8_t>& getPixels() const;

private:
	std::vector<uint8_t> mPixels;      // Stores RGB values sequentially
	int mWidth{ 0 };                 // Image width
	int mHeight{ 0 };                // Image height
	int mMaxRange{ 0 };              // Maximum color value
};

#endif // PPM_HPP