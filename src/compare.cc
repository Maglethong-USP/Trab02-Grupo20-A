#include "Image.hh"


int main(int argc, char *argv[])
{
	Image img1, img2;

	img1.Read("doc/outputs/lena_color_s.ppm");
	img2.Read("doc/outputs/lena_color_p.ppm");

	if(img1 == img2)
		std::cout << "Yes!\n"
	else
		std::cout << "No!\n"

	return 0;
}