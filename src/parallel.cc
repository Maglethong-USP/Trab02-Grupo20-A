#include "Image.hh"

#include "mpi.h"





int main(int argc, char *argv[])
{
	int noProcesses;
	int processID;
	char computerName[MPI_MAX_PROCESSOR_NAME];
	int nameSize;
	MPI_Status Stat;

	// Initializing PMI
	if( MPI_Init(&argc, &argv) != MPI_SUCCESS )
		return 1;

	if(argc < 5)
	{
		std::cout << "Usage: \n";
		std::cout << argv[0] << " Inputfile Outputfile num_vertical_splits num_horizontal_splits [MPI args]\n";
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Finalize();
		return 0;
	}

	MPI_Comm_size(MPI_COMM_WORLD, &noProcesses);
	MPI_Comm_rank(MPI_COMM_WORLD, &processID);
	MPI_Get_processor_name(computerName, &nameSize);



	Image img;
	int verticalSlices = atoi(argv[3]);
	int horizontalSlices = atoi(argv[4]);

	int width, height;
	int size;
	int color;
	char *imgArray = NULL;

	// Master Rank
	if(processID == 0)
	{
		// Read image
		img.Read(argv[1]);

		// Split image and send fragments to other processes
		std::vector<Image> imgList = img.Split(verticalSlices, horizontalSlices);
		int largestSize = Image::GetImageArraySize(imgList[0].GetWidth(), imgList[0].GetHeight(), imgList[0].GetColor());
		imgArray = new char[largestSize];

		for(int i=0; i<imgList.size(); i++)
		{
			int dest = i+1;
			size = Image::GetImageArraySize(imgList[i].GetWidth(), imgList[i].GetHeight(), imgList[i].GetColor());
			if(size > largestSize) // Shouldn't happen but lets be safe
				return 1;
			imgList[i].GetImageAsArray(imgArray);

			color = imgList[i].GetColor();
			width = imgList[i].GetWidth();
			height = imgList[i].GetHeight();

			MPI_Send(&color, 	1, 		MPI_INT, 	dest, 0, MPI_COMM_WORLD);
			MPI_Send(&width, 	1, 		MPI_INT, 	dest, 1, MPI_COMM_WORLD);
			MPI_Send(&height, 	1, 		MPI_INT, 	dest, 2, MPI_COMM_WORLD);
			MPI_Send(&imgArray, size, 	MPI_CHAR, 	dest, 3, MPI_COMM_WORLD);
		}

		// Wait for them to Respond
		for(int i=0; i<imgList.size(); i++)
		{
			int source = i+1;
			color = imgList[i].GetColor();
			width = imgList[i].GetWidth();
			height = imgList[i].GetHeight();

			size = Image::GetImageArraySize(width, height, color);
			MPI_Recv(imgArray, size, MPI_CHAR, source, 4, MPI_COMM_WORLD, &Stat);
			imgList[i].SetFromArray(imgArray, width, height, color);
		}

		// Merge and write results
		img.Merge(imgList, verticalSlices);
		img.Write(argv[2]);

		delete[] imgArray;
	}
	// Children
	else
	{
		// Receive instructions from Master
		int source = 0;

		MPI_Recv(&color, 	1, MPI_INT, source, 0, MPI_COMM_WORLD, &Stat);
		MPI_Recv(&width, 	1, MPI_INT, source, 1, MPI_COMM_WORLD, &Stat);
		MPI_Recv(&height, 	6, MPI_INT, source, 2, MPI_COMM_WORLD, &Stat);
		size = Image::GetImageArraySize(width, height, (bool) color);
		imgArray = new char[size];
		MPI_Recv(&imgArray, size, MPI_CHAR, source, 3, MPI_COMM_WORLD, &Stat);

		// Execute and Respond
		img.SetFromArray(imgArray, width, height, color);
		img.Smooth_WhithouBorders();

		// Respond
		img.GetImageAsArray(imgArray);
		MPI_Send(&imgArray, size, MPI_CHAR, source, 4, MPI_COMM_WORLD);


		delete[] imgArray;
	}

	MPI_Barrier(MPI_COMM_WORLD);

	// Finalize
	MPI_Finalize();

	return 0;
}



