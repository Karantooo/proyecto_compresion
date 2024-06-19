#include "Lempel_Ziv.h"
#include "Lempel_Ziv_Descompresion.h"

int main(){

    //std::string texto = "C:/Users/rica1/OneDrive/Escritorio/proyecto_compresion/pruebas.txt";
    std::string texto = "C:/Users/rica1/OneDrive/Escritorio/textos de prueba/sources_20mb.txt";
    Lempel_ziv_compresion(texto, 10);
    decode("C:/Users/rica1/OneDrive/Escritorio/proyecto_compresion/output/LZ_compression.dat");
    
}