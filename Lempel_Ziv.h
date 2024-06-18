#ifndef LEMPEL_ZIV_H 
#define LEMPEL_ZIV_H

#include <iostream>
#include <fstream>
#include "trie.h"
#include "flag_pair.h"

/**
 * @brief 
 * 
 * @param mensaje 
 * @return std::pair<TrieNode, std::string> 
 */
void Lempel_ziv_compresion(std::string ruta_archivo, int largo_subcadenas){

    TrieNode* compression_trie = new TrieNode();
    std::vector<flag_pair> compresion;
    std::string texto;
    std::string subcadena;
    int largo = 0;
    int largo_max_subcadena;
    bool codificando_subcadena = false;
    std::ifstream file(ruta_archivo);

    if(file.is_open()){

        char c;
        while(file.peek() != EOF){

            file.get(c);
            std::string tmp_string(1, static_cast<unsigned char>(c));
            texto.append(tmp_string);
        
        }
        file.close();

    }else{

        std::cerr << "No se pudo abrir el archivo." << std::endl;

    }

    largo = texto.size();
    for(int i=0 ; i<largo ; i++){

        std::string tmp_char(1, static_cast<unsigned char>(texto[i]));
        std::pair<int, int>* rango_cadena = new std::pair<int, int>;
        std::pair<int, int>* rango_caracter = search_key(compression_trie, tmp_char);


        //Si el caracter mensaje[i] no aparecio anteriormente.
        if(rango_caracter == nullptr){

            //si no hay una subcadena en formacion, se ingresa el caracter mensaje[i] al trie y se agrega a la compresion.
            if(!codificando_subcadena){

                insert_key(compression_trie, tmp_char, i);
                flag_pair tmp_pair;
                tmp_pair = flag_pair(static_cast<unsigned char>(tmp_char[0]), 0);
                compresion.push_back(tmp_pair);

            //Si hay una subcadena en formacion, se agrega la compresion de la subcadena formada y luego la de mensaje[i], ademas mensaje[i] se agrega al trie.
            }else{

                insert_key(compression_trie, tmp_char, i);
                rango_cadena = search_key(compression_trie, subcadena);
                subcadena.clear();
                flag_pair tmp_pair(rango_cadena->first, rango_cadena->second);
                compresion.push_back(tmp_pair);
                tmp_pair = flag_pair(static_cast<unsigned char>(tmp_char[0]), 0);
                compresion.push_back(tmp_pair);
                codificando_subcadena = false;

            }

        //Si mensaje[i] ya aparecio anteriormente.
        } else{

            //Si no hay una subcadena en formación, se crea una subcadena y se declara en una variable que hay una subcadena en formacion.
            if(!codificando_subcadena){

                if(i == largo - 1){

                    flag_pair tmp_pair(rango_caracter->first, rango_caracter->second);
                    compresion.push_back(tmp_pair);
                    break;

                }
                subcadena.append(tmp_char);
                largo_max_subcadena = i;
                codificando_subcadena = true;
                

            //Si hay una subcadena en formacion.
            }else{
                
                //Se verifica si la subcadena concatenada a mensaje[i] forma una subcadena que haya aparecido antes en el texto, si no ha aparecido antes, se agrega la subcadena sin mensaje[i], se limpia el contenido de la subcadena y se le agrega mensaje[i].
                std::string tmp_subcadena = subcadena + tmp_char;
                rango_cadena = search_key(compression_trie, tmp_subcadena);
                if(rango_cadena == nullptr || rango_cadena->second > largo_max_subcadena){

                    rango_cadena = search_key(compression_trie, subcadena);
                    flag_pair tmp_pair(rango_cadena->first, rango_cadena->second);
                    compresion.push_back(tmp_pair);
                    subcadena.clear();
                    subcadena.append(tmp_char);

                    //Si se llega al ultimo caracter del mensaje se añade a la codificacion el ultimo caracter.
                    if(i == largo - 1){

                        tmp_pair = flag_pair(rango_caracter->first, rango_caracter->second);
                        compresion.push_back(tmp_pair);
                        break;

                    }
                    largo_max_subcadena = i;

                //si la concatenacion forma una subcadena que haya aparecido antes, la subcadena pasa a ser la concatenacion.
                }else{

                    subcadena.append(tmp_char);
                    //Si se llega al ultimo caracter del mensaje se añade a la codificacion toda la subcadena formada hasta el momento.
                    if(i == largo - 1){
                        
                        flag_pair tmp_pair(rango_cadena->first, rango_cadena->second);
                        compresion.push_back(tmp_pair);
                        
                    }

                }

            }
        }

        //Se agregan al trie todas las subcadenas que se puedan formar con los i primeros caracteres del mensaje, y que posiblemente no se hayan formado antes.
        for(int j=0 ; j<i ; j++){

            int inicio = i - (j + 1);
            std::string tmp_sub = texto.substr(inicio, j+2);
            rango_cadena = search_key(compression_trie, tmp_sub);
            if(!rango_cadena){
                insert_key(compression_trie, tmp_sub, inicio);
            }
            if(j == largo_subcadenas){
                break;
            }
        }

        //Se eliminan los punteros creados en el bucle.
        delete rango_cadena;
        delete rango_caracter;
    }

    //Se cierra el archivo y se elimina el trie.
    delete compression_trie;

    //Guardar la codificacion en un archivo binario
    std::fstream file1;
    file1.open("LZ_compression.dat", std::ios::out | std::ios::binary);
    if(file1){

        int tamano = compresion.size();
        for(int i=0 ; i<tamano ; i++){

            flag_pair tmp_pair = compresion[i];
            file1.write(reinterpret_cast<char*>(&(tmp_pair.index)), sizeof(int));
            file1.write(reinterpret_cast<char*>(&(tmp_pair.module)), sizeof(int));

        }
        file1.close();

    }else{
        std::cerr << "Error al abrir el archivo.";
    }

}

#endif