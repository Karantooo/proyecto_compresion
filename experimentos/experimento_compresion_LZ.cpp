#include <iostream>
#include <chrono>
#include "../Lempel_Ziv.h"

int main(int argc, char* argv[]){
	auto start = std::chrono::high_resolution_clock::now();
    	Lempel_ziv compresor(argv[1], std::stoi(argv[2]));
    	compresor.compress();
    	auto end = std::chrono::high_resolution_clock::now();

    	double compressing_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    	compressing_time *= 1e-9;

	Lempel_ziv decompresor("LZ_compression.dat");
    	start = std::chrono::high_resolution_clock::now();
    	decompresor.decompress();
    	end = std::chrono::high_resolution_clock::now();
    	double decompressing_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    	decompressing_time *= 1e-9;

	std::cout << std::stoi(argv[2]) << ";" << compressing_time << ";" << decompressing_time << std::endl;


}
