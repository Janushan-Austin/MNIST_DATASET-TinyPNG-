#include <TinyPngOut.hpp>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>


int main() {

	int numberOfItems;
	char *MSB_Array = new char[sizeof(int)];
	int rows, cols;
	char * iterator = (char*)&numberOfItems;

	FILE *f_images;
	f_images = fopen("res/MNIST_DATASET/train-images.idx3-ubyte", "rb");


	fread(MSB_Array, 1, 1, f_images);
	fread(MSB_Array, 1, 1, f_images);
	fread(MSB_Array, 1, 1, f_images);
	fread(MSB_Array, 1, 1, f_images);

	for (int i = 0; i < sizeof(int); i++) {
		fread(&MSB_Array[i], 1, 1, f_images);
	}


	for (int i = sizeof(int) - 1; i >= 0; i--) {
		*iterator = MSB_Array[i];
		iterator = iterator + 1;
	}
	
	iterator = (char*)&rows;

	for (int i = 0; i < sizeof(int); i++) {
		fread(&MSB_Array[i], 1, 1, f_images);
	}


	for (int i = sizeof(int) - 1; i >= 0; i--) {
		*iterator = MSB_Array[i];
		iterator = iterator + 1;
	}

	iterator = (char*)&cols;

	for (int i = 0; i < sizeof(int); i++) {
		fread(&MSB_Array[i], 1, 1, f_images);
	}


	for (int i = sizeof(int) - 1; i >= 0; i--) {
		*iterator = MSB_Array[i];
		iterator = iterator + 1;
	}

	for (int i = 0; i < numberOfItems; i++) {
		std::string pngName = "MNIST_TESTSET_";
		pngName += ('0' + i);
		pngName += ".png";
		std::ofstream out("imgs/" + pngName, std::ios::binary);
		TinyPngOut PNG_create(cols, rows, out);
	
		std::uint8_t *pixels = new std::uint8_t[rows*cols*3];

		
		for (int k =0; k < rows*cols*3; k+=3) {
			char curr;
			fread(&curr, 1, 1, f_images);
			pixels[k + 1] = pixels[k + 2] = pixels[k] = curr;
		}
		PNG_create.write(pixels, rows*cols);

	}

	std::cin.get();




	return 0;
}