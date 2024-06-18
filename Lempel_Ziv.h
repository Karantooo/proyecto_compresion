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
void Lempel_ziv_compresion(std::string ruta_archivo){

    TrieNode* compression_trie = new TrieNode();
    std::vector<flag_pair> compresion;
    std::string subcadena;
    int largo = 0;
    bool codificando_subcadena = false;
    std::ifstream file(ruta_archivo);

    if(file.is_open()){

        char c;
        while(file.get(c)){
            largo++;
        }
        file.clear();
        file.seekg(0, std::ios::beg);

        for(int i=0 ; i<largo ; i++){

            file.get(c);
            std::string tmp_char(1, c);
            std::pair<int, int>* rango_cadena = new std::pair<int, int>;
            std::pair<int, int>* rango_caracter = search_key(compression_trie, tmp_char);


            //Si el caracter mensaje[i] no aparecio anteriormente.
            if(rango_caracter == nullptr){

                //si no hay una subcadena en formacion, se ingresa el caracter mensaje[i] al trie y se agrega a la compresion.
                if(!codificando_subcadena){

                    insert_key(compression_trie, tmp_char, i);
                    flag_pair tmp_pair;
                    tmp_pair = flag_pair(static_cast<unsigned char>(c), 0);
                    compresion.push_back(tmp_pair);

                //Si hay una subcadena en formacion, se agrega la compresion de la subcadena formada y luego la de mensaje[i], ademas mensaje[i] se agrega al trie.
                }else{

                    insert_key(compression_trie, tmp_char, i);
                    rango_cadena = search_key(compression_trie, subcadena);
                    subcadena.clear();
                    flag_pair tmp_pair(rango_cadena->first, rango_cadena->second);
                    compresion.push_back(tmp_pair);
                    tmp_pair = flag_pair(static_cast<unsigned char>(c), 0);
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
                    codificando_subcadena = true;
                    

                //Si hay una subcadena en formacion.
                }else{
                    
                    //Se verifica si la subcadena concatenada a mensaje[i] forma una subcadena que haya aparecido antes en el texto, si no ha aparecido antes, se agrega la subcadena sin mensaje[i], se limpia el contenido de la subcadena y se le agrega mensaje[i].
                    rango_cadena = search_key(compression_trie, subcadena + tmp_char);
                    if(rango_cadena == nullptr){

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
                file.seekg(inicio, std::ios::beg);
                std::string tmp_sub;
                for(int k = 0 ; k<j+2 ; k++){

                    file.get(c);
                    std::string file_char(1, c);
                    tmp_sub.append(file_char);

                }
                rango_cadena = search_key(compression_trie, tmp_sub);
                if(!rango_cadena){

                    insert_key(compression_trie, tmp_sub, inicio);

                }
                if(j == 10){
                    break;
                }
            }

            //Se devuelve el cursor posicion del archivo a la posicion donde estaba antes de agregar las subcadenas.
            file.seekg(i + 1, std::ios::beg);

            //Se eliminan los punteros creados en el bucle.
            delete rango_cadena;
            delete rango_caracter;
        }

        //Se cierra el archivo y se elimina el trie.
        file.close();
        delete compression_trie;

        //Guardar la codificacion en un archivo binario
        std::fstream file1;
        file1.open("LZ_compression.bin", std::ios::out | std::ios::binary);
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

    }else{
        std::cerr << "No se pudo abrir el archivo." << std::endl;
    }

}

#endif