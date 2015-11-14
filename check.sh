#!/bin/sh



echo "Creating directories"
mkdir bin doc doc/outputs


echo "Compiling [Sequencial]"
g++ ./src/Image.cc ./src/Pixel.cc ./src/sequencial.cc -o bin/sequencial
echo "Compiling [Seq-Split]"
g++ ./src/Image.cc ./src/Pixel.cc ./src/split.cc -o bin/split
echo "Compiling [Palallel]"
mpiCC ./src/Image.cc ./src/Pixel.cc ./src/parallel.cc -o bin/parallel
echo "Compiling [Compare]"
g++ ./src/Image.cc ./src/Pixel.cc ./src/compare.cc -o bin/compare


echo "Running [Sequencial]"
./bin/sequencial ./doc/inputs/lena_color.ppm ./doc/outputs/lena_s.ppm 
echo "Running [Seq-Split]"
./bin/split ./doc/inputs/lena_color.ppm ./doc/outputs/lena_s_split.ppm 
echo "Running [Palallel]"
mpirun ./bin/parallel ./doc/inputs/lena_color.ppm ./doc/outputs/lena_p.ppm 2 2 -np 5 -hosts node03,node04,node06,node07,node08

echo "Running Compare [Sequencial]-[Seq-Split]"
./bin/compare ./doc/outputs/lena_s.ppm ./doc/outputs/lena_s_split.ppm
echo "Running Compare [Sequencial]-[Palallel]"
./bin/compare ./doc/outputs/lena_s.ppm ./doc/outputs/lena_p.ppm
echo "Running Compare [Seq-Split]-[Palallel]"
./bin/compare ./doc/outputs/lena_s_split.ppm ./doc/outputs/lena_p.ppm


