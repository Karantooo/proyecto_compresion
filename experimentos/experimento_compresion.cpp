#include <iostream>
#include <chrono>
#include <Lempel_Ziv.h>
#include <huffman.h>
#include <filesystem>

int main(int argc, char* argv[]){
    std::filesystem::path filename1 = argv[1];
    std::filesystem::path filename2 = argv[2];
    double filesize1 = std::filesystem::file_size(filename1.c_str());
    filesize1 /= 1024;
	double filesize2 = std::filesystem::file_size(filename2.c_str());
    filesize2 /= 1024;

    HuffmanCoding codificador(argv[1]);
    auto start = std::chrono::high_resolution_clock::now();
    codificador.enconde();
    auto end = std::chrono::high_resolution_clock::now();
    double coding_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    coding_time *= 1e-9;
    
    Lempel_ziv compresor(argv[1], std::stoi(argv[2]));
    start = std::chrono::high_resolution_clock::now();
    compresor.compress();
    end = std::chrono::high_resolution_clock::now();
    double compressing_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    compressing_time *= 1e-9;

    std::cout << filesize1 << ";" << coding_time << ";" << filesize2 << ";" << compressing_time << std::endl;
}