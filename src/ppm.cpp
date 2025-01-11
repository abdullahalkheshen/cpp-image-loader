#include "ppm.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

namespace {
    // Constants
    constexpr const char* MAGIC_NUMBER = "P3";
    constexpr int MAX_COLOR_VALUE = 255;
    constexpr int MIN_DIMENSION = 1;
    constexpr int MAX_DIMENSION = 10000;  // Reasonable max dimension to prevent memory issues

    // Helper functions
    bool isComment(const std::string& line) {
        return !line.empty() && line[0] == '#';
    }

    void validateDimensions(int width, int height) {
        if (width < MIN_DIMENSION || height < MIN_DIMENSION ||
            width > MAX_DIMENSION || height > MAX_DIMENSION) {
            throw std::runtime_error("Invalid dimensions: Width and height must be between " +
                std::to_string(MIN_DIMENSION) + " and " +
                std::to_string(MAX_DIMENSION));
        }
    }

    void validateColorRange(int range) {
        if (range <= 0 || range > MAX_COLOR_VALUE) {
            throw std::runtime_error("Invalid color range: Must be between 1 and " +
                std::to_string(MAX_COLOR_VALUE));
        }
    }

    void validatePixelCount(size_t pixelCount, int width, int height) {
        if (pixelCount != static_cast<size_t>(width) * height * 3) {
            throw std::runtime_error("Invalid pixel count: Expected " +
                std::to_string(width * height * 3) +
                " values, but got " + std::to_string(pixelCount));
        }
    }
}

PPM::PPM(const std::string& filename) {
    std::ifstream file(filename, std::ios::in);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    enum class ParseState { MAGIC_NUMBER, DIMENSIONS, COLOR_RANGE, PIXELS };
    ParseState state = ParseState::MAGIC_NUMBER;

    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || isComment(line)) {
            continue;
        }

        std::istringstream stream(line);
        std::string token;

        while (stream >> token) {
            try {
                switch (state) {
                case ParseState::MAGIC_NUMBER:
                    if (token != MAGIC_NUMBER) {
                        throw std::runtime_error("Invalid format: Expected " +
                            std::string(MAGIC_NUMBER));
                    }
                    state = ParseState::DIMENSIONS;
                    break;

                case ParseState::DIMENSIONS:
                    mWidth = std::stoi(token);
                    if (!(stream >> token)) {
                        throw std::runtime_error("Missing height value");
                    }
                    mHeight = std::stoi(token);
                    validateDimensions(mWidth, mHeight);
                    state = ParseState::COLOR_RANGE;
                    break;

                case ParseState::COLOR_RANGE:
                    mMaxRange = std::stoi(token);
                    validateColorRange(mMaxRange);
                    state = ParseState::PIXELS;
                    // Reserve space for all pixels to prevent reallocations
                    mPixels.reserve(mWidth * mHeight * 3);
                    break;

                case ParseState::PIXELS:
                    int value = std::stoi(token);
                    if (value < 0 || value > mMaxRange) {
                        throw std::runtime_error("Pixel value out of range: " +
                            std::to_string(value));
                    }
                    mPixels.push_back(value);
                    break;
                }
            }
            catch (const std::exception& e) {
                throw std::runtime_error("Error parsing PPM file: " + std::string(e.what()));
            }
        }
    }

    validatePixelCount(mPixels.size(), mWidth, mHeight);
}

PPM::~PPM() = default;

void PPM::savePPM(const std::string& outFilename) const {
    std::ofstream file(outFilename);
    if (!file) {
        throw std::runtime_error("Failed to create output file: " + outFilename);
    }

    // Write header
    file << MAGIC_NUMBER << '\n'
        << mWidth << ' ' << mHeight << '\n'
        << mMaxRange << '\n';

    // Write pixel data
    for (size_t i = 0; i < mPixels.size(); ++i) {
        file << mPixels[i];
        if ((i + 1) % 3 == 0) {
            file << '\n';  // Newline after each pixel (RGB triplet)
        }
        else {
            file << ' ';   // Space between RGB values
        }
    }

    if (!file) {
        throw std::runtime_error("Error writing to file: " + outFilename);
    }
}

void PPM::lighten() {
    const int increment = mMaxRange / 2;
    std::transform(mPixels.begin(), mPixels.end(), mPixels.begin(),
        [=](int pixel) { return std::min(pixel + increment, mMaxRange); });
}

void PPM::darken() {
    const int decrement = mMaxRange / 2;
    std::transform(mPixels.begin(), mPixels.end(), mPixels.begin(),
        [=](int pixel) { return std::max(pixel - decrement, 0); });
}

// Additional utility methods
void PPM::clear() {
    mPixels.clear();
    mWidth = 0;
    mHeight = 0;
    mMaxRange = 0;
}

bool PPM::isValid() const {
    return mWidth > 0 && mHeight > 0 && mMaxRange > 0 &&
        mPixels.size() == static_cast<size_t>(mWidth) * mHeight * 3;
}

// Optional: Add getters for width, height, and pixel access
int PPM::getWidth() const { return mWidth; }
int PPM::getHeight() const { return mHeight; }
int PPM::getMaxRange() const { return mMaxRange; }

const std::vector<int>& PPM::getPixels() const { return mPixels; }