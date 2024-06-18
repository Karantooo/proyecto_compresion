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
    std::ofstream decodificado("decode.txt");
    while(file.peek() != EOF){
        int index;
        int module;
        file.read(reinterpret_cast<char*> (&index), sizeof(int));
        file.read(reinterpret_cast<char*> (&module), sizeof(int));
        if(!module){
            unsigned char c = static_cast<unsigned char>(index);
            std::string tmp_string(1, c);
            mensaje.append(tmp_string);
        }
        else{
            for(int i = index; i < index + module; i++){
                mensaje += mensaje[i];
            }
        }
    }
    decodificado << mensaje;
    file.close();
    decodificado.close();
}

#endif