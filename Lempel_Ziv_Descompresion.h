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
    std::string posicion;
    std::string cantidad;
    char c;
    for(int i = 0; i < codificacion.length(); i++){
        c = codificacion[i];
        if(c == '('){
            for(int j = i + 1; codificacion[j] != ','; j++){
                if(isalpha(codificacion[j])){
                    mensaje += codificacion[j];
                    break;
                }
                else if(isdigit(codificacion[j])){
                    posicion += codificacion[j];
                }
            }
        }
        else if(c == ','){
            for(int j = i + 1; codificacion[j] != ')'; j++){
                if(codificacion[j] == '0'){
                    break;
                }
                else if(isdigit(codificacion[j])){
                    cantidad += codificacion[j];
                }
            }
        }
        else if(c == ')'){
            if(codificacion[i - 1] != '0'){
                for(int j = stoi(posicion); j < stoi(cantidad); j++){
                    mensaje += mensaje[j];
                }
                posicion.clear();
                cantidad.clear();
            }
        }
    }
    return mensaje;
}
#endif