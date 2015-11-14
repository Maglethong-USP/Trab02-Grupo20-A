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

	img.Read(argv[1]);
	img.Smooth();
	img.Write(argv[2]);

	return 0;
}
