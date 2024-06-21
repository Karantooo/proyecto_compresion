#include <iostream>
#include <chrono>
#include <Lempel_Ziv.h>
#include <huffman.h>

int main(int argc, char* argv[]){
    auto start = std::chrono::high_resolution_clock::now();
    HuffmanCoding codificador(argv[1]);
    codificador.enconde();
    auto end = std::chrono::high_resolution_clock::now();
    double coding_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    coding_time *= 1e-9;
    
    start = std::chrono::high_resolution_clock::now();
    Lempel_ziv compresor(argv[1], std::stoi(argv[2]));
    compresor.compress();
    end = std::chrono::high_resolution_clock::now();
    double compressing_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    compressing_time *= 1e-9;
}