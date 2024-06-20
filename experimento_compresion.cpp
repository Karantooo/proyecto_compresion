#include <iostream>
#include <chrono>
#include <Lempel_Ziv.h>

int main(int argc, char* argv[]){
    Lempel_ziv compresor(argv[1], std::stoi(argv[2]));
    auto start = std::chrono::high_resolution_clock::now();
    compresor.compress();
    auto end = std::chrono::high_resolution_clock::now();
    double running_time1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    running_time1 *= 1e-9;
    start = std::chrono::high_resolution_clock::now();
    compresor.decompress();
    end = std::chrono::high_resolution_clock::now();
    double running_time2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    running_time2 *= 1e-9;
}