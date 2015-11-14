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


void Pixel::Write(std::ostream &out)
{
	char c;
	c = (char)this->r;
	out.write( &c, 1);
	c = (char)this->g;
	out.write( &c, 1);
	c = (char)this->b;
	out.write( &c, 1);
}

void Pixel::Read(std::istream &in)
{
		char c;
		in.read( &c, 1);
		this->r = (p_type) c;
		in.read( &c, 1);
		this->g = (p_type) c;
		in.read( &c, 1);
		this->b = (p_type) c;
}

void Pixel::Write(std::ostream &out, int chanel)
{
	char c;
	c = (char)(*this)[chanel];
	out.write( &c, 1);
}

void Pixel::Read(std::istream &in, int chanel)
{
	char c;
	in.read( &c, 1);
	(*this)[chanel] = (p_type) c;
}
