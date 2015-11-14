#include "Image.hh"


int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		std::cout << "Usage: \n";
		std::cout << argv[0] << " imagefile1 imagefile2\n";
		return 0;
	}

	Image img1, img2;

	img1.Read(argv[1]);
	img2.Read(argv[2]);

	if(img1 == img2)
		std::cout << "Yes!\n";
	else
		std::cout << "No!\n";

	return 0;
}
