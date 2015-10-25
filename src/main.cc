
#include "Image.hh"


int main(int argc, char *argv[])
{

	Image i;


	i.Read("lena_color.ppm");
	i.Smooth();
	i.Write("new.ppm");

	//i.Read("test.ppm");

	//i.Write("testOut.ppm");


	return 0;
}