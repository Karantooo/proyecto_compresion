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
        bool int_flag;
        int index;
        int module;
        file.read(reinterpret_cast<char*> (&int_flag), sizeof(bool));
        file.read(reinterpret_cast<char*> (&index), sizeof(int));
        file.read(reinterpret_cast<char*> (&module), sizeof(int));
        if(module == 0){
            if(!int_flag){
                unsigned char c = static_cast<unsigned char>(index);
                std::string tmp_string(1, c);
                mensaje.append(tmp_string);
            }else{
                mensaje.append(std::to_string(index));
            }
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