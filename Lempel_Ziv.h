#ifndef LEMPEL_ZIV_H 
#define LEMPEL_ZIV_H

#include <iostream>
#include "trie.h"

//Lempel_ziv debe devolver un archivo con la compresion del mensaje y el trie para descomprimir el archivo
std::pair<TrieNode, std::string> Lempel_Ziv(std::string mensaje){
    TrieNode* compression_trie = new TrieNode();
    std::string codificacion;
    std::string palabra;
    std::string tmp_codificacion;
    int largo = mensaje.size();
    for(int i=0 ; i<largo ; i++){
        //Si el caracter es un espacio y la palabra no está vacia, guardo la palabra.
        if(mensaje[i] == ' ' && !palabra.empty()){
            std::pair<int, int>* rango_palabra;
            //El metodo find devuelve un pair con un indice al inicio y al final de la palabra, o nullptr si no se encontro antes en el mensaje
            rango_palabra = search_key(compression_trie, palabra);
            //Si la palabra estaba en el trie, se añade a la codificacion un parentesis con el indice inicial y final
            if(rango_palabra!=nullptr){
                codificacion.append('('+std::to_string(rango_palabra->first)+','+std::to_string(rango_palabra->second));
            //Si no se encontro antes se añade la palabra al trie y se agregan sus caracteres a la compresion individualmente
            }else{
                codificacion.append(tmp_codificacion);
                compression_trie.insert(palabra, i-palabra.size());
            }
            //Se reinicia la palabra y la codificacion de caracteres guardados
            tmp_codificacion.clear();
            palabra.clear();
        //Si el caracter es distinto al 'espacio' se añade el caracter a la palabra en formacion
        } else if(mensaje[i] != ' '){
            palabra.append(std::to_string(mensaje[i]));
        }


        std::pair<int, int>* rango_caracter;
        rango_caracter = search_key(compression_trie, std::to_string(mensaje[i]));
    
        //Verifica si el caracter aparecio anteriormente y crea una codificacion temporal caracter a caracter
        if(rango_caracter == nullptr){
            compression_trie.insert(mensaje[i], i);
            tmp_codificacion.append("("+mensaje[i]+','+std::to_string(0)+')');
        } else{
            tmp_codificacion.append("("+std::to_string(rango_caracter->first)+','+std::to_string(rango_caracter->second)+')');
        }
    }
}

#endif