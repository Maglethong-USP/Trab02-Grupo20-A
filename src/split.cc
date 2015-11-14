#include "Image.hh"


int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		std::cout << "Usage: \n";
		std::cout << argv[0] << " Inputfile Outputfile\n";
		return 0;
	}

	Image img;
	Image part;

	int verticalSlices = 4;
	int horizontalSlices = 2;

	int width, height;
	int size;
	int color;
	char *imgArray = NULL;

	img.Read(argv[1]);


	// Split image and send fragments to other processes
	std::vector<Image> imgList = img.Split(verticalSlices, horizontalSlices);
	int largestSize = Image::GetImageArraySize(imgList[0].GetWidth(), imgList[0].GetHeight(), imgList[0].GetColor());
	imgArray = new char[largestSize];

	for(int i=0; i<imgList.size(); i++)
	{
		size = Image::GetImageArraySize(imgList[i].GetWidth(), imgList[i].GetHeight(), imgList[i].GetColor());
		imgList[i].GetImageAsArray(imgArray);

		color = imgList[i].GetColor();
		width = imgList[i].GetWidth();
		height = imgList[i].GetHeight();

		part.SetFromArray(imgArray, width, height, color);
		part.Smooth_WhithouBorders();
		part.GetImageAsArray(imgArray);


		imgList[i].SetFromArray(imgArray, width, height, color);
	}
	delete[] imgArray;

	img.Merge(imgList, verticalSlices);



	img.Write(argv[2]);

	return 0;
}
