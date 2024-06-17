#ifndef LEMPEL_ZIV_DESCOMPRESION
#define LEMPEL_ZIV_DESCOMPRESION

#include <iostream>
#include "trie.h"

/**
 * @brief 
 * 
 * @param mensaje 

 */
void decode(std::string ruta_archivo){
    std::string mensaje;
    std::fstream file;
    file.open(ruta_archivo, std::ios::in | std::ios::binary);
    std::fstream decodificado;
    decodificado.open("decode.txt");
    while(file.peek() != EOF){
        bool flag;
        int index;
        int module;
        file.read(reinterpret_cast<char *> (&flag), sizeof(bool));
        file.read(reinterpret_cast<char *> (&index), sizeof(int));
        file.read(reinterpret_cast<char *> (&module), sizeof(int));
        if(!flag){
            char c = index;
            mensaje += c;
        }
        else{
            for(int i = index; i <= module; i++){
                mensaje += mensaje[i];
            }
        }
    }
    decodificado << mensaje;
    file.close();
    decodificado.close();
}
#endif