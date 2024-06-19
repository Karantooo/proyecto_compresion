#include "Lempel_Ziv.h"

int main(){

    std::string texto = "./LZ_compression.dat";
    //std::string texto = "C:/Users/rica1/OneDrive/Escritorio/textos de prueba/sources_20mb.txt";
    Lempel_ziv compresor(texto);
    // compresor.compress();
    compresor.decompress();
    
}