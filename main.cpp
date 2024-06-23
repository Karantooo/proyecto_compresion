#include "Lempel_Ziv.h"

int main(){

    // std::string texto = "./LZ_compression.dat";
    std::string texto = "../textos/shakespeare.txt";
    Lempel_ziv compresor(texto, 10);
    compresor.compress();
}