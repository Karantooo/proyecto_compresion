#ifndef LEMPEL_ZIV_H 
#define LEMPEL_ZIV_H

#include <iostream>
#include "trie.h"

/**
 * @brief 
 * 
 * @param mensaje 
 * @return std::pair<TrieNode, std::string> 
 */
std::string Lempel_Ziv(std::string mensaje){
    TrieNode* compression_trie = new TrieNode();
    std::string codificacion;
    std::string palabra;
    std::string tmp_codificacion;
    std::string cod_espacio;
    int largo = mensaje.size();
    for(int i=0 ; i<largo ; i++){
        std::pair<int, int>* rango_caracter;
        std::string tmp_char(1, mensaje[i]);
        rango_caracter = search_key(compression_trie, tmp_char);
    
        //Verifica si el caracter aparecio anteriormente y crea una codificacion temporal caracter a caracter
        if(rango_caracter == nullptr){
            std::string tmp_char(1, mensaje[i]);
            insert_key(compression_trie, tmp_char, i);
            if(tmp_char == " "){
                cod_espacio = "("+tmp_char+","+std::to_string(0)+")";
            }else{
                tmp_codificacion.append("("+tmp_char+","+std::to_string(0)+")");
            }
        } else{
            if(tmp_char == " "){
                cod_espacio = "("+std::to_string(rango_caracter->first)+","+std::to_string(rango_caracter->second)+")";
            }else{
                tmp_codificacion.append("("+std::to_string(rango_caracter->first)+","+std::to_string(rango_caracter->second)+")");
            }
            
        }

        //Si el caracter es distinto al 'espacio' se añade el caracter a la palabra en formacion
        if(mensaje[i] != ' '){
            std::string tmp_char(1, mensaje[i]);
            palabra.append(tmp_char);
        //Si el caracter es un espacio y la palabra no está vacia, o si es la ultima palabra, guardo la palabra.
        }
        if((mensaje[i] == ' ' && !palabra.empty()) || i==largo-1){
            std::pair<int, int>* rango_palabra;
            //El metodo find devuelve un pair con un indice al inicio y al final de la palabra, o nullptr si no se encontro antes en el mensaje
            rango_palabra = search_key(compression_trie, palabra);
            //Si la palabra estaba en el trie, se añade a la codificacion un parentesis con el indice inicial y final
            if(rango_palabra!=nullptr){
                codificacion.append("("+std::to_string(rango_palabra->first)+","+std::to_string(rango_palabra->second)+")");
                if(mensaje[i]==' '){
                    codificacion.append(cod_espacio);
                }
            //Si no se encontro antes se añade la palabra al trie y se agregan sus caracteres a la compresion individualmente
            }else{
                codificacion.append(tmp_codificacion);
                if(mensaje[i]==' '){
                    codificacion.append(cod_espacio);
                }
                insert_key(compression_trie, palabra, i-palabra.size());
            }
            //Se reinicia la palabra y la codificacion de caracteres guardados
            tmp_codificacion.clear();
            palabra.clear();
        }
    }

    return codificacion;
}

#endif