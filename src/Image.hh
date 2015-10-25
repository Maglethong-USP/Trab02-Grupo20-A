#include "Pixel.hh"

#include <iostream>
#include <fstream>
#include <string>


//! Channel color enumeration
enum Image_File_Mode { BINARY, TEXT };

class Image
{
private:
	int width, height;
	Pixel *image;

public:
	Image();
	Image(int width, int height);
	~Image();

	int Read(const char *fileName);

	int Write(const char *fileName);
	int Write(const char *fileName, const int mode);

	//! Smooth image
	void Smooth();

private:
	void Init(int width, int height);

	int ReadPlainText(std::ifstream &stream);

	int ReadBinary(std::ifstream &stream);

	int WritePlainText(std::ofstream &stream);

	int WriteBinary(std::ofstream &stream);

	Pixel & GetPixel(int i, int j);
};