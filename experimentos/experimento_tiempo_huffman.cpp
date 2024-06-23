#include <iostream>
#include <chrono>
#include "../Lempel_Ziv.h"
#include "../huffman.h"
#include <filesystem>

int main(int argc, char* argv[]){
    std::filesystem::path filename1 = argv[1];
    double filesize1 = std::filesystem::file_size(filename1.c_str());

    HuffmanCoding codificador(argv[1]);
    auto start = std::chrono::high_resolution_clock::now();
    codificador.enconde();
    auto end = std::chrono::high_resolution_clock::now();
    double coding_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    coding_time *= 1e-9;

    std::cout << filesize1 << ";" << coding_time << std::endl;
}