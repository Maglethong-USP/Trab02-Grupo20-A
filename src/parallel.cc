#include "Image.hh"

#include "mpi.h"


int main(int argc, char *argv[])
{
        int noProcesses;
        int processID;
        char computerName[MPI_MAX_PROCESSOR_NAME];
        int nameSize;

        // Initializing PMI
        if( MPI_Init(&argc, &argv) != MPI_SUCCESS )
                return 1;

        MPI_Comm_size(MPI_COMM_WORLD, &noProcesses);
        MPI_Comm_rank(MPI_COMM_WORLD, &processID);
        MPI_Get_processor_name(computerName, &nameSize);


        // Master Rank
        if(processID == 0)
        {
                std::cout << "Master! @ " << computerName << "\n";
        }
        // Children
        else
        {
                std::cout << processID << "@" << computerName << "\n";
        }






        MPI_Barrier(MPI_COMM_WORLD);




        // Finalize
        MPI_Finalize();

        return 0;




        Image img1;
        img1.Read("../../Images/Small(2048x1024).ppm");

        img1.Smooth();
        img1.Write("SmallSmoothed.ppm");
}



