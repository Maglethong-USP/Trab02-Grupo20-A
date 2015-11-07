#include "Pixel.hh"

#include <iostream>
#include <fstream>
#include <vector>


//! Channel color enumeration
/*!
	First bit  -> Color/Black&Wite
	Second bit -> Text/Binary
*/
enum Image_File_Mode 
{ 
	BW_TEXT			= 0, // 00
	BW_BINARY		= 1, // 01
	COLOR_TEXT		= 2, // 10
	COLOR_BINARY	= 3  // 11
};

class Image
{
private:
public: // TODO
	int width, height;
	Pixel *image;

public:
	Image();
	Image(int width, int height);
	Image(Image *other);
	~Image();

	int Read(const char *fileName);

	int Write(const char *fileName);
	int Write(const char *fileName, const int mode);

	//! Smooth image
	void Smooth();

	void Smooth_WhithouBorders(); // TODO

	std::vector<Image> Split(int vertical, int horizontal);

	void Merge(std::vector<Image> &others, int verticalSplits);

	void Merge(Image &other, int line, int column);

private:
public: // TODO
	void Init(int width, int height);

	int ReadPlainText(std::ifstream &stream);

	int ReadBinary(std::ifstream &stream);

	int WritePlainText(std::ofstream &stream);

	int WriteBinary(std::ofstream &stream);

	Pixel & GetPixel(int i, int j);

	Pixel SmoothedPixel(int i, int j);

	//! Sets image as a copy of a portion of another image
	/*!
		This method takes into account that the user might want to copy outside
		of borders. In this case the method copies the closest image value.

		NOTE: line and column values may go out of the other image's border by
		ONLY 1

		@param other
	*/
	void SetWithSubimage(Image &other, int line, int column, int width, int height);


public:

	//! [Operator Overload] Copy
	Image& operator = (const Image& other)
	{
		if (this != &other)
		{
			if(this->image != NULL)
				delete[] this->image;
			this->Init(other.width, other.height);
			for(int i=0; i<this->width *this->height; i++)
				this->image[i] = other.image[i];
		}
		return *this;
	}

	//! [Operator Overload] Comparison
	inline bool operator == (const Image& other)
	{
		if( this->width != other.width ||
			this->height != other.height)
			return false;

		for(int i=0; i<this->width *height; i++)
			if(this->image[i] != other.image[i])
				return false;

		return true;
	}
	inline bool operator != (const Image& other)
	{
		return !(*this == other);
	}
};