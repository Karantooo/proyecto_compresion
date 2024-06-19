#include "Lempel_Ziv.h"

int main(){

    std::string texto = "C:/Users/rica1/OneDrive/Escritorio/proyecto_compresion/pruebas.txt";
    //std::string texto = "C:/Users/rica1/OneDrive/Escritorio/textos de prueba/sources_20mb.txt";
    Lempel_ziv compresor(texto, 10);
    compresor.compress();
    compresor.decompress();
    
}