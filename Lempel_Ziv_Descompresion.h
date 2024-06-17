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

    /*for(int i = 0; i < codificacion.length(); i++){
        c = codificacion[i];
        if(c == '('){
            for(int j = i + 1; codificacion[j] != ','; j++){
                if(!isdigit(codificacion[j])){
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
    */
}
#endif