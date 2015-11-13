#include "Image.hh"



Image::Image()
{
	this->width = -1;
	this->height = -1;
	this->image = NULL;
	this->color = false;
}

Image::Image(int width, int height)
{
	this->Init(width, height);
}

Image::Image(Image *other)
{
	if(other->width > 0 && other->height > 0)
	{
		this->Init(other->width, other->height);
		for(int i=0; i<this->height *this->width; i++)
			this->image[i] = other->image[i];
		this->color = other->color;
	}
	else
	{
		this->width = -1;
		this->height = -1;
		this->image = NULL;
		this->color = false;
	}
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
	this->color = false;
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
		mode = COLOR_BINARY;
	else if(tmp[0] == 'P' && tmp[1] == '3')
		mode = COLOR_TEXT;
	// TODO [Imagen PGM]
	this->color = true;

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
	if(mode == COLOR_BINARY)
		this->ReadBinary(stream);
	else if(mode == COLOR_TEXT)
		this->ReadPlainText(stream);

	stream.close();
}

int Image::Write(const char *fileName){ this->Write(fileName, COLOR_BINARY); }

int Image::Write(const char *fileName, const int mode)
{
	std::ofstream stream;
	stream.open(fileName);

	// Write mode
	if(mode == COLOR_BINARY)
		stream << "P6\n";
	else if(mode == COLOR_TEXT)
		stream << "P3\n";
	// TODO [Imagen PGM]

	// Write dimensions
	stream << this->width << ' ' << this->height << "\n";

	// Write pixel range
	stream << "255" << "\n";

	// Write image
	if(mode == COLOR_BINARY)
		this->WriteBinary(stream);
	else if(mode == COLOR_TEXT)
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
	// TODO [use SetWithSubimage once tested]
	Image extended_copy;

	extended_copy.SetWithSubimage(*this, -1, -1, this->width +2, this->height +2);

	// Smooth using extended image
	for(int i=0; i< this->height; i++)
		for(int j=0; j<this->width; j++)
			this->GetPixel(i, j) = extended_copy.SmoothedPixel(i +1, j +1);
}

void Image::Smooth_WhithouBorders()
{
	// Copy so we don't use altered pixels for smooth calculation
	Image copy(this);

	// Smooth using copy
	for(int i=1; i< this->height -1; i++)
		for(int j=1; j<this->width -1; j++)
			this->GetPixel(i, j) = copy.SmoothedPixel(i, j);
}

Pixel & Image::GetPixel(int i, int j)
{
	return this->image[i *this->width +j];
}

Pixel Image::SmoothedPixel(int i, int j)
{
	Pixel ret;

	// Calculate Average
	int sum[3] = {0, 0, 0};
	for(int color=0; color<3; color++)
	{
		for(int h = i-1; h<=i+1; h++)
			for(int w = j-1; w<=j+1; w++)
				sum[color] += this->GetPixel(h, w)[color];

		// Save new Value
		ret[color] = (p_type) (sum[color]/9);
	}

	return ret;
}

std::vector<Image> Image::Split(int vertical, int horizontal)
{
	std::vector<Image> ret(vertical *horizontal);

	int start_i;
	int start_j;
	int end_i;
	int end_j;

	int height = this->height/vertical;
	int width = this->width/horizontal;
	int curImage = 0;


	start_i = 0;
	end_i = height -1;

	for(int i=0; i<vertical; i++)
	{
		start_j = 0;
		end_j = width -1;

		for(int j=0; j<horizontal; j++)
		{
			ret[curImage].SetWithSubimage(	*this, start_i -1, start_j -1, 
											end_j -start_j +2 +1, end_i -start_i +2 +1);

			start_j = end_j +1;

			if(j < horizontal -2)
				end_j += width;
			else // Last gets rest
				end_j = this->width -1;

			curImage++;
		}
		
		start_i = end_i +1;

		if(i < vertical -2)
			end_i += height;
		else // Last gets rest
			end_i = this->height -1;
	}

	return ret;
}

void Image::SetWithSubimage(Image &other, int line, int column, int width, int height)
{
	this->Init(width, height);
	this->color = other.color;

	int line_min 	= (line < 0) 						? 0 : line;
	int column_min 	= (column < 0) 						? 0 : column;
	int line_max	= (line +height >= other.height) 	? other.height -1 : line +height -1;
	int column_max	= (column +width >= other.width) 	? other.width -1 : column +width -1;


	// Copy Center
	for(int i=1; i<height -1; i++)
		for(int j=1; j<width -1; j++)
			this->GetPixel(i, j) = other.GetPixel(line +i, column +j);
	
	// Top Border
	for(int j=1; j<width -1; j++)
		this->GetPixel(0, j) = other.GetPixel(line_min, column +j);

	// Bottom Border
	for(int j=1; j<width -1; j++)
		this->GetPixel(height -1, j) = other.GetPixel(line_max, column +j);

	// Left Border
	for(int i=1; i<height -1; i++)
		this->GetPixel(i, 0) = other.GetPixel(line +i, column_min);

	// Right Border
	for(int i=1; i<height -1; i++)
		this->GetPixel(i, width -1) = other.GetPixel(line +i, column_max);

	// Vertices
	this->GetPixel(0, 0) 				= other.GetPixel(line_min, column_min);
	this->GetPixel(0, width -1) 		= other.GetPixel(line_min, column_max);
	this->GetPixel(height -1, 0) 		= other.GetPixel(line_max, column_min);
	this->GetPixel(height -1, width -1) = other.GetPixel(line_max, column_max);
}

void Image::Merge(std::vector<Image> &others, int verticalSplits)
{
	int horizontalSplits = others.size()/verticalSplits;
	int curImage = 0;
	int curLine = 0;
	int curColumn = 0;

	for(int i=0; i<horizontalSplits; i++)
	{
		curColumn = 0;
		for(int j=0; j<verticalSplits; j++)
		{
			this->Merge(others[curImage], curLine, curColumn);

			curColumn += others[curImage].width -2;
			curImage++;
		}
		curLine += others[curImage -1].height -2;
	}
}

void Image::Merge(Image &other, int line, int column)
{
	for(int i=0; i<other.height-2; i++)
		for(int j=0; j<other.width-2; j++)
			this->GetPixel(line +i, column +j) = other.GetPixel(i+1, j+1);
}



int Image::GetWidth()
{
	return this->width;
}

int Image::GetHeight()
{
	return this->height;
}
bool Image::GetColor()
{
	return this->color;
}

void Image::GetImageAsArray(char *image)
{
	if(this->color)
		for(int i=0; i<this->height *this->width; i++)
		{
			image[i *3 +0] = this->image[i][0];
			image[i *3 +1] = this->image[i][1];
			image[i *3 +2] = this->image[i][2];
		}
	else
		for(int i=0; i<this->height *this->width; i++)
		{
			image[i] = this->image[i][0];
		}
}

int Image::GetImageArraySize(int width, int heigh, bool color)
{
	if(this->color)
		return this->height *this->width *3;
	else
		return this->height *this->width;
}


void Image::SetFromArray(const char *array, int width, int height, bool color)
{
	if(this->image != null)
		delete[] this->image;

	this->Init(width, height);
	this->color = color;

	if(color)
		for(int i=0; i< width *height; i++)
		{
			this->image[i][0] = array[i *3 +0];
			this->image[i][1] = array[i *3 +1];
			this->image[i][2] = array[i *3 +2];
		}
	else
		for(int i=0; i< width *height; i++)
		{
			this->image[i][0] = array[i];
		}
}