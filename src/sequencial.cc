#include "Image.hh"


int main(int argc, char *argv[])
{
        Image img1;

        img1.Read("../../Images/Small(2048x1024).ppm");
        img1.Smooth();
        img1.Write("SmallSmoothed.ppm");

        return 0;
}
