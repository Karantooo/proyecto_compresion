#ifndef LEMPEL_ZIV_H 
#define LEMPEL_ZIV_H

#include <iostream>
#include <fstream>
#include "trie.h"
#include "flag_pair.h"



/**
 * @brief 
 * 
 */
class Lempel_ziv{

private:
    TrieNode* compression_trie;
    std::vector<flag_pair> compression;
    std::string texto;
    std::string ruta_archivo;
    std::string ruta_archivo_comprimido;
    int largo_subcadenas;
public:
    Lempel_ziv(std::string, int);
    void compress();
    void decompress();

private:
    void read_file();
    void find_substrings(int);
    void make_compressed_file();

};



/**
 * @brief Construct a new Lempel_ziv::Lempel_ziv object
 * 
 * @param ruta_archivo 
 * @param largo_subcadenas 
 */
Lempel_ziv::Lempel_ziv(std::string ruta_archivo, int largo_subcadenas) : ruta_archivo(ruta_archivo), largo_subcadenas(largo_subcadenas){}



/**
 * @brief 
 * 
 */
void Lempel_ziv::read_file(){

    std::ifstream file(ruta_archivo);

    if(file.is_open()){

        texto.clear();
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

}



/**
 * @brief Se agregan al trie todas las subcadenas que se puedan formar con los i primeros caracteres del mensaje, y que posiblemente no se hayan formado antes.
 * 
 * @param i 
 */
void Lempel_ziv::find_substrings(int i){

    std::pair<int, unsigned char>* rango_cadena;

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
}



/**
 * @brief 
 * 
 */
void Lempel_ziv::compress(){

    read_file();

    compression_trie = new TrieNode();
    std::string subcadena;
    int largo = texto.size();
    int largo_max_subcadena;
    bool codificando_subcadena = false;

    for(int i=0 ; i<largo ; i++){

        std::string tmp_char(1, static_cast<unsigned char>(texto[i]));
        std::pair<int, unsigned char>* rango_cadena = new std::pair<int, unsigned char>;
        std::pair<int, unsigned char>* rango_caracter = search_key(compression_trie, tmp_char);


        //Si el caracter mensaje[i] no aparecio anteriormente.
        if(rango_caracter == nullptr){

            //si no hay una subcadena en formacion, se ingresa el caracter mensaje[i] al trie y se agrega a la compresion.
            if(!codificando_subcadena){

                insert_key(compression_trie, tmp_char, i);
                flag_pair tmp_pair;
                tmp_pair = flag_pair(static_cast<unsigned char>(tmp_char[0]), 0);
                compression.push_back(tmp_pair);

            //Si hay una subcadena en formacion, se agrega la compresion de la subcadena formada y luego la de mensaje[i], ademas mensaje[i] se agrega al trie.
            }else{

                insert_key(compression_trie, tmp_char, i);
                rango_cadena = search_key(compression_trie, subcadena);
                subcadena.clear();
                flag_pair tmp_pair(rango_cadena->first, rango_cadena->second);
                compression.push_back(tmp_pair);
                tmp_pair = flag_pair(static_cast<unsigned char>(tmp_char[0]), 0);
                compression.push_back(tmp_pair);
                codificando_subcadena = false;

            }

        //Si mensaje[i] ya aparecio anteriormente.
        } else{

            //Si no hay una subcadena en formación, se crea una subcadena y se declara en una variable que hay una subcadena en formacion.
            if(!codificando_subcadena){

                if(i == largo - 1){

                    flag_pair tmp_pair(rango_caracter->first, rango_caracter->second);
                    compression.push_back(tmp_pair);
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
                    compression.push_back(tmp_pair);
                    subcadena.clear();
                    subcadena.append(tmp_char);

                    //Si se llega al ultimo caracter del mensaje se añade a la codificacion el ultimo caracter.
                    if(i == largo - 1){

                        tmp_pair = flag_pair(rango_caracter->first, rango_caracter->second);
                        compression.push_back(tmp_pair);
                        break;

                    }
                    largo_max_subcadena = i;

                //si la concatenacion forma una subcadena que haya aparecido antes, la subcadena pasa a ser la concatenacion.
                }else{

                    subcadena.append(tmp_char);
                    //Si se llega al ultimo caracter del mensaje se añade a la codificacion toda la subcadena formada hasta el momento.
                    if(i == largo - 1){
                        
                        flag_pair tmp_pair(rango_cadena->first, rango_cadena->second);
                        compression.push_back(tmp_pair);
                        
                    }

                }

            }
        }

        find_substrings(i);

        //Se eliminan los punteros creados en el bucle.
        delete rango_cadena;
        delete rango_caracter;
    }

    //Se cierra el archivo y se elimina el trie.
    delete compression_trie;

    make_compressed_file();

}



/**
 * @brief 
 * 
 */
void Lempel_ziv::make_compressed_file(){

    //Guardar la codificacion en un archivo binario
    std::fstream file;
    flag_pair tmp_pair;
    ruta_archivo_comprimido = "LZ_compression.dat";
    file.open(ruta_archivo_comprimido, std::ios::out | std::ios::binary);
    if(file){

        int tamano = compression.size();
        for(int i=0 ; i<tamano ; i++){

            tmp_pair = compression[i];
            file.write(reinterpret_cast<char*>(&(tmp_pair.index)), sizeof(int));
            file.write(reinterpret_cast<char*>(&(tmp_pair.module)), sizeof(unsigned char));

        }
        file.close();

    }else{
        std::cerr << "Error al abrir el archivo.";
    }
    
}



/**
 * @brief 
 * 
 */
void Lempel_ziv::decompress(){

    std::string mensaje;
    std::fstream file;
    file.open(ruta_archivo_comprimido, std::ios::in | std::ios::binary);
    std::ofstream decodificado("decode.txt");
    while(file.peek() != EOF){
        int index;
        unsigned char module;
        file.read(reinterpret_cast<char*> (&index), sizeof(int));
        file.read(reinterpret_cast<char*> (&module), sizeof(unsigned char));
        if(module == 0){

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