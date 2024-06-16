#ifndef LEMPEL_ZIV_DESCOMPRESION
#define LEMPEL_ZIV_DESCOMPRESION

#include <iostream>
#include "trie.h"

/**
 * @brief 
 * 
 * @param mensaje 
 * @return std::string 
 */
std::string Lempel_Ziv(std::string codificacion){
    std::string mensaje;
    char c;
    for(int i = 0; i < codificacion.length(); i+=2){
        c = codificacion[i];
        if(isalpha(c)){
            mensaje += c;
        }
    }
}
#endif