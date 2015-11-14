#!/bin/sh
times_to_execute=10

# Saving script start time
echo "Starting Experiment at: " >> execTime
date >> execTime
echo "==================================================" >> execTime

# Compile sequential and parallel versions
make

# Remove any previous out directory
rm -r ./out

# Create output directory
mkdir ./out

# Run for each Image in sequential
echo "Starting Sequential Experiments: " >> execTime
for inFile in "ExtraLarge(16384x8192).pgm" "Large(8192x4096).pgm" "Medium(4096x2048).pgm" "Small(2048x1024).ppm" "ExtraLarge(16384x8192).ppm" "Large(8192x4096).ppm" "Medium(4096x2048).ppm" "Small(2048x1024).pgm"
do
	for i in $(seq 1 $times_to_execute)
	do
		in_file_name="../../Images/"$inFile
		out_file_name="./out/trash"

		start=$(date +%s.%N)

	#	./bin/sequencial $in_file_name $out_file_name

		dur=$(echo "$(date +%s.%N) - $start" | bc)

		message="Using image "$in_file_name" experiment #"$i" took "$dur
		echo $message >> execTime
	done
done

# Run for each Image in sequential
echo "Starting Sequential Experiments: " >> execTime
for inFile in "ExtraLarge(16384x8192).pgm" "Large(8192x4096).pgm" "Medium(4096x2048).pgm" "Small(2048x1024).ppm" "ExtraLarge(16384x8192).ppm" "Large(8192x4096).ppm" "Medium(4096x2048).ppm" "Small(2048x1024).pgm"
do
	for i in $(seq 1 $times_to_execute)
	do
		in_file_name="../../Images/"$inFile
		out_file_name="./out/trash"

		start=$(date +%s.%N)

	#	./bin/parallel $in_file_name $out_file_name 2 2 -np 4 -hostfile ../../hosts

		dur=$(echo "$(date +%s.%N) - $start" | bc)

		message="Using image "$in_file_name" experiment #"$i" took "$dur
		echo $message >> execTime
	done
done

echo "Ended Experiment at: " >> execTime
date >> execTime



