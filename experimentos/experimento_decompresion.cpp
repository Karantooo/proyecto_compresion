#include <iostream>
#include <chrono>
#include "../Lempel_Ziv.h"
#include "../huffman.h"
#include <filesystem>

int main(int argc, char* argv[]){
    std::filesystem::path filename1 = argv[1];
    std::filesystem::path filename2 = argv[2];
    double filesize1 = std::filesystem::file_size(filename1.c_str());
    filesize1 /= 1024;
	double filesize2 = std::filesystem::file_size(filename2.c_str());
    filesize2 /= 1024;

    HuffmanCoding decodificador(argv[1]);
    auto start = std::chrono::high_resolution_clock::now();
    decodificador.decode();
    auto end = std::chrono::high_resolution_clock::now();
    double decoding_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    decoding_time *= 1e-9;
    
    start = std::chrono::high_resolution_clock::now();
    Lempel_ziv decompresor((argv[2]));
    decompresor.decompress();
    end = std::chrono::high_resolution_clock::now();
    double decompressing_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    decompressing_time *= 1e-9;
    std::cout << filesize1 << ";" << decoding_time << ";" << filesize2 << ";" << decompressing_time << std::endl;
}