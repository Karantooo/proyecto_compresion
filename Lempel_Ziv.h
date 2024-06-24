#ifndef LEMPEL_ZIV_H 
#define LEMPEL_ZIV_H

#include <iostream>
#include <fstream>
#include "trie.h"
#include "flag_pair.h"



/**
 * @brief Clase que implementa el algoritmo de compresion Lempel-Ziv.
 * 
 * @param compression_trie: Trie que almacena las subcadenas que se han formado con los caracteres del mensaje.
 * @param compression: Vector que almacena la codificacion de las subcadenas del mensaje.
 * @param texto: Mensaje que se va a comprimir.
 * @param ruta_archivo: Ruta del archivo que se va a comprimir.
 * @param ruta_archivo_comprimido: Ruta del archivo comprimido, se usa para la descompresión.
 * @param largo_subcadenas: Largo maximo de las subcadenas que se van a formar con los caracteres del mensaje
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
    Lempel_ziv(std::string);
    void compress();
    void decompress();

private:
    void read_file();
    void find_substrings(int);
    void make_compressed_file();

};



/**
 * @brief Constructor usado para para la compresion del archivo.
 * 
 * @param ruta_archivo ruta del archivo que se va a comprimir
 * @param largo_subcadenas largo maximo de las subcadenas que se van a formar con los caracteres del mensaje
 */
Lempel_ziv::Lempel_ziv(std::string ruta_archivo, int largo_subcadenas) : ruta_archivo(ruta_archivo), largo_subcadenas(largo_subcadenas){}

/**
 * @brief Constructor usado para la descompresion del archivo.
 * 
 * @param ruta_archivo ruta del archivo a descomprimir.
 */
Lempel_ziv::Lempel_ziv(std::string ruta_archivo) : ruta_archivo_comprimido(ruta_archivo){}



/**
 * @brief metodo que lee el archivo que se va a comprimir.
 * 
 */
void Lempel_ziv::read_file(){

    std::ifstream file(ruta_archivo);

    if(file.is_open()){

        //Limpia el contenido del string texto, por si ya se leyo otro texto antes.
        texto.clear();
        char c;
        //Lee el archivo caracter por caracter y lo almacena en el string texto.
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
 * @brief Se agregan al trie todas las subcadenas que se puedan formar con los i primeros caracteres del mensaje y que no se hayan agregado antes.
 * 
 * @param i indica la posicion del carácter actual en el mensaje.
 */
void Lempel_ziv::find_substrings(int i){

    std::pair<int, unsigned char>* rango_cadena;

    //Se forman las subcadenas que se pueden formar con los ultimos j + 1 caracteres del mensaje, contando el final como el caracter i.
    for(int j=0 ; j<i ; j++){

        int inicio = i - (j + 1);
        std::string tmp_sub = texto.substr(inicio, j+2);
        rango_cadena = search_key(compression_trie, tmp_sub);
        if(!rango_cadena){
            insert_key(compression_trie, tmp_sub, inicio);
        }
        //si j llega a ser igual al largo de las subcadenas, se termina el bucle. Esto para disminuir el tiempo de ejecución y la cantidad de ram
        //usada por el programa.
        if(j == largo_subcadenas){
            break;
        }
    }
}



/**
 * @brief Se encarga de comprimir el archivo leido con read_file()
 * 
 */
void Lempel_ziv::compress(){

    read_file();

    //largo_max_subcadena se usa para saber el largo máximo que puede tener la subcadena que se esta formando.
    compression_trie = new TrieNode();
    std::string subcadena;
    int largo = texto.size();
    int largo_max_subcadena;
    bool codificando_subcadena = false;

    //Se recorre el mensaje caracter por caracter.
    for(int i=0 ; i<largo ; i++){

        //Se crea un string con el caracter 'mensaje[i]' para poder buscarlo en el trie.
        std::string tmp_char(1, static_cast<unsigned char>(texto[i]));
        std::pair<int, unsigned char>* rango_cadena = new std::pair<int, unsigned char>;
        std::pair<int, unsigned char>* rango_caracter = search_key(compression_trie, tmp_char);


        //Si 'tmp_char' no aparecio anteriormente en el mensaje.
        if(rango_caracter == nullptr){

            //si no hay una subcadena en formacion, se ingresa el caracter 'tmp_char' al trie con posicion de inicio 0 lo cual
            //indica que es la primera vez que se ve, luego se agrega a la compresion.
            if(!codificando_subcadena){

                insert_key(compression_trie, tmp_char, i);
                flag_pair tmp_pair;
                tmp_pair = flag_pair(static_cast<unsigned char>(tmp_char[0]), 0);
                compression.push_back(tmp_pair);

            //Si hay una subcadena en formacion, se agrega la compresion de la subcadena formada y luego la de 'tmp_char', ademas 'tmp_char' 
            //se agrega al trie, finalmente se declara que ya no se esta formando una subcadena.
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

        //Si 'tmp_char' ya aparecio anteriormente.
        } else{

            //Si no hay una subcadena en formación.
            if(!codificando_subcadena){

                //Si se llega al ultimo caracter del mensaje se añade a la codificacion el ultimo caracter.
                if(i == largo - 1){

                    flag_pair tmp_pair(rango_caracter->first, rango_caracter->second);
                    compression.push_back(tmp_pair);
                    break;

                }
                //Se crea la subcadena y se declara que hay una subcadena en formacion, ademas, se establece el largo máximo que puede tener esa
                //subcadena.
                subcadena.append(tmp_char);
                largo_max_subcadena = i;
                codificando_subcadena = true;
                

            //Si hay una subcadena en formacion.
            }else{
                
                //Se verifica si la subcadena concatenada a 'tmp_char' forma una subcadena que haya aparecido antes en el texto o si el largo
                //de la nueva subcadena es mayor al largo maximo que se le permitia, si no ha aparecido antes o si supera el largo máximo, se 
                //agrega la subcadena sin 'tmp_char', se limpia el contenido de la subcadena y se le agrega 'tmp_char'.
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

        //Agrega todas las subcadenas que se pueden formar con 2 a 'largo_subcadenas' ultimos carácteres del mensaje que se hayan revisado actualmente y que no se hayan agregado antes.
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
 * @brief Guarda la codificacion del texto en un archivo binario.
 * 
 */
void Lempel_ziv::make_compressed_file(){

    //Guardar la codificacion en un archivo binario
    std::fstream file;
    flag_pair tmp_pair;
    ruta_archivo_comprimido = "LZ_compression.dat";
    file.open(ruta_archivo_comprimido, std::ios::out | std::ios::binary);
    if(file){

        //Por cada par de la codificacion se guarda el indice y el modulo en el archivo.
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
 * @brief Descomprime el archivo binario que contiene un archivo comprimido por LZ.
 * 
 */
void Lempel_ziv::decompress(){

    std::string mensaje;
    std::fstream file;
    file.open(ruta_archivo_comprimido, std::ios::in | std::ios::binary);
    std::ofstream decodificado("decode.txt");
    //Se lee el archivo binario y se decodifica el mensaje.
    while(file.peek() != EOF){
        int index;
        unsigned char module;
        file.read(reinterpret_cast<char*> (&index), sizeof(int));
        file.read(reinterpret_cast<char*> (&module), sizeof(unsigned char));
        //Si el modulo es 0, se agrega el caracter correspondiente al indice al mensaje, si no, se agregan los 'module' caracteres desde el indice
        //'index' que estan en el mensaje
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
    //Se guarda el mensaje decodificado en un archivo de texto.
    decodificado << mensaje;
    file.close();
    decodificado.close();

}

#endif