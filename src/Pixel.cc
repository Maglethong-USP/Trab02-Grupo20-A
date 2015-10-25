#include "Pixel.hh"




Pixel::Pixel()
{
	this->Init(0, 0, 0);
}


Pixel::Pixel(const p_type r, const p_type g, const p_type b)
{
	this->Init(r, g, b);
}

Pixel::~Pixel()
{
}

void Pixel::Init(const p_type r, const p_type g, const p_type b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

std::string Pixel::ToString()
{
	std::ostringstream stream;

	stream << "(";
	stream << (int) this->r;
	stream << ", ";
	stream << (int) this->g;
	stream << ", ";
	stream << (int) this->b;
	stream << ")";

	return stream.str();
}