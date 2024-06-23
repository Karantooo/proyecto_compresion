#include <iostream>
#include <chrono>
#include <filesystem>
#include "../Lempel_Ziv.h"

int main(int argc, char* argv[]){
	std::filesystem::path filename = argv[1];	
	double filesize = std::filesystem::file_size(filename.c_str());

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

	std::filesystem::path f_comprimido = "LZ_compression.dat";
    double comprimido = std::filesystem::file_size(f_comprimido.c_str());
    double compression_percentage = (comprimido / filesize) * 100;

	std::cout << std::stoi(argv[2]) << ";" << compressing_time << ";" << decompressing_time << ";" << compression_percentage <<std::endl;


}
