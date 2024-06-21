#include <iostream>
#include <chrono>
#include "../Lempel_Ziv.h"
#include "../huffman.h"

int main(int argc, char* argv[]){
    HuffmanCoding decodificador(argv[1]);
    auto start = std::chrono::high_resolution_clock::now();
    decodificador.decode();
    auto end = std::chrono::high_resolution_clock::now();
    double decoding_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    decoding_time *= 1e-9;
    std::cout << "tiempo de decodificacion: " << decoding_time;
    
    start = std::chrono::high_resolution_clock::now();
    Lempel_ziv decompresor(argv[1], std::stoi(argv[2]));
    decompresor.decompress();
    end = std::chrono::high_resolution_clock::now();
    double decompressing_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    decompressing_time *= 1e-9;
}