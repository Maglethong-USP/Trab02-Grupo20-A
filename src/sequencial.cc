#include "Image.hh"


int main(int argc, char *argv[])
{
	Image img;

	img.Read("doc/inputs/lena_color.ppm");
	img.Smooth();
	img.Write("doc/outputs/lena_color_s.ppm");

	return 0;
}
