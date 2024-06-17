#include "Lempel_Ziv.h"
#include "Lempel_Ziv_Descompresion.h"

int main(){
    //std::string texto = "C:/Users/rica1/OneDrive/Escritorio/proyecto_compresion/pruebas.txt";
    std::string texto = "C:/Users/rica1/OneDrive/Escritorio/textos de prueba/shakespeare.txt";
    Lempel_ziv_compresion(texto);
    decode("C:/Users/rica1/OneDrive/Escritorio/proyecto_compresion/output/LZ_compression.bin");
    
}