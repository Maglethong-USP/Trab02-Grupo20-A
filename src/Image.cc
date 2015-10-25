#include "Image.hh"



Image::Image()
{
	this->width = -1;
	this->height = -1;
	this->image = NULL;
}

Image::Image(int width, int height)
{
	this->Init(width, height);
}

Image::~Image()
{
	if(this->image != NULL)
		delete[] this->image;
}


void Image::Init(int width, int height)
{
	this->width = width;
	this->height = height;
	this->image = new Pixel[this->width *this->height];
}



int Image::Read(const char *fileName)
{
	std::ifstream stream;
	stream.open(fileName);

	std::string tmp;

	// Read mode
	int mode;
	stream >> tmp;
	if(tmp[0] == 'P' && tmp[1] == '6')
		mode = BINARY;
	else if(tmp[0] == 'P' && tmp[1] == '3')
		mode = TEXT;

	// Read dimensions
	int width, height;
	stream >> width >> height;

	// Read pixel range
	int range;
	stream >> range;

	// Read image
	char garbage;
	stream.read(&garbage, 1); // reading whitespace
	if(this->image != NULL)
		delete[] this->image;
	this->Init(width, height);
	if(mode == BINARY)
		this->ReadBinary(stream);
	else if(mode == TEXT)
		this->ReadPlainText(stream);

	stream.close();
}

int Image::Write(const char *fileName){ this->Write(fileName, BINARY); }

int Image::Write(const char *fileName, const int mode)
{
	std::ofstream stream;
	stream.open(fileName);

	// Write mode
	if(mode == BINARY)
		stream << "P6\n";
	else if(mode == TEXT)
		stream << "P3\n";

	// Write dimensions
	stream << this->width << ' ' << this->height << "\n";

	// Write pixel range
	stream << "255" << "\n";

	// Write image
	if(mode == BINARY)
		this->WriteBinary(stream);
	else if(mode == TEXT)
		this->WritePlainText(stream);

	stream.close();
}


int Image::ReadPlainText(std::ifstream &stream)
{
	std::cout << "Reading P3 image not implemented!\n";
}

int Image::ReadBinary(std::ifstream &stream)
{
	for(int i=0; i<this->width *this->height; i++)
		stream >> this->image[i];
}

int Image::WritePlainText(std::ofstream &stream)
{
	std::cout << "Writing P3 image not implemented!\n";
}

int Image::WriteBinary(std::ofstream &stream)
{
	for(int i=0; i<this->width *this->height; i++)
		stream << this->image[i];
}

void Image::Smooth()
{
	
	// Copy so we don't use altered pixels for smooth calculation
	Image extended_copy(this->width +2, this->height +1);
	for(int i=0; i<this->height; i++)
	{
		for(int j=0; j<this->width; j++)
			extended_copy.GetPixel(i +1, j+1) = this->GetPixel(i, j);
		// Left/Right borders copy closest values
		extended_copy.GetPixel(i +1, 0) = this->GetPixel(i, 1);
		extended_copy.GetPixel(i +1, this->width +1) = this->GetPixel(i, this->width -1);
	}
	// Top/Bottom borders copies closest value
	for(int j=0; j<this->width+2; j++)
	{
		// Left/Right borders copy closest values
		extended_copy.GetPixel(0, j) = this->GetPixel(1, j);
		extended_copy.GetPixel(this->height +1, j) = this->GetPixel(this->height -1, j);
	}

	// Smooth using extended image
	for(int i=0; i< this->height; i++)
		for(int j=0; j<this->width; j++)
		{
			// Calculate Average
			int sum[3] = {0, 0, 0};
			for(int color=0; color<3; color++)
			{
				for(int h = i-1; h<=i+1; h++)
					for(int w = j-1; w<=j+1; w++)
						sum[color] += extended_copy.GetPixel(h+1, w+1)[color];

				// Save new Value
				this->GetPixel(i, j)[color] = (p_type) (sum[color]/9);
			}
		}
}

Pixel & Image::GetPixel(int i, int j)
{
	return this->image[i *this->width +j];
}