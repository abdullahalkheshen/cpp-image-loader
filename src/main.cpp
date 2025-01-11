#include "ppm.hpp"
#include <iostream>

void test1() {
	PPM myPPM("./myppm_p3.ppm");
	myPPM.lighten();
	myPPM.savePPM("../myppm_p3_lightened.ppm");
}

void test2() {
	PPM myPPM("./myppm_p3.ppm");
	myPPM.darken();
	myPPM.savePPM("../myppm_p3_darkened.ppm");
}

int main() {
	test1();
	//test2();
	return EXIT_SUCCESS;
}