
#include "Image.hh"


int main(int argc, char *argv[])
{

	Image img1, img2;


	//img.Read("lena_color.ppm");
	//img.Smooth();
	//img.Write("normalSmooth.ppm");


	img1.Read("lena_color.ppm");
	img2.Read("lena_color.ppm");

	int split_X = 2;
	int split_Y = 2;


	std::vector<Image> s = img1.Split(split_X, split_Y);


	img2.Smooth();
	img2.Write("normalSmooth.ppm");

	for(int i=0; i<s.size(); i++)
		s[i].Smooth_WhithouBorders();
	img1.Merge(s, split_X);
	img1.Write("splitSmooth.ppm");


	if(img1 == img2)
		std::cout << "Same! \n";
	else
		std::cout << "Diferent! \n";

	return 0;
}