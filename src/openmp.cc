#include "Image.hh"

#include "omp.h"

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		std::cout << "Usage: \n";
		std::cout << argv[0] << " Inputfile Outputfile\n";
		return 0;
	}

	Image img;

	img.Read(argv[1]);


	std::vector<Image> imgList = img.Split(1, 1);

	Image copy;
	copy = imgList[0];

	#pragma omp parallel for
	for(int i=1; i<img.GetHeight() -1; i++)
	{
		imgList[0].Smooth_Line_WhithouBorders(i, copy);
	}



	imgList[0].Write(argv[2]);

	return 0;
}
