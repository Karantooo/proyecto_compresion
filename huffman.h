#pragma once
#include <unordered_map>
#include <string>
#include <queue>
#include <fstream>
#include <iostream>
#include <bitset>
#include "MinHeap.h"
/**
 * @brief archivo que tiene la implementacion de huffman 
 * Este archivo esta basado en el codigo disponible en geeks for geeks haciendo modificaciones.
 * @link https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
 */


class HuffmanCoding{
    private:
        std::unordered_map<char, int> frecuencia_caracter;
        std::unordered_map<char, std::string> symbols;
        std::fstream file;
        std::priority_queue<MinHeapNode*, std::vector<MinHeapNode*>, 
            compare> minHeap; 
        std::fstream pre_order_file, in_order_file;
        std::fstream pre_order_read, in_order_read;
        std::string ruta, ruta_inorder, ruta_preorder;

        std::vector<MinHeapNode> preorder_tree;
        std::vector<MinHeapNode> inorder_tree;

        MinHeapNode* dictionary_tree;

        std::vector<std::string> lineas_codificadas;

        unsigned short int exceso_ultimo_chunk;


        
    public:
        /**
         * @brief Construct a new Huffman Coding object
         * Si se usa este constructor es que se quiere comprimir el archivo de esta ruta
         * @param ruta ruta del achivo a comprimir
         */
        HuffmanCoding(std::string ruta): ruta(ruta){
            file.open(ruta);
            std::string word;
            ruta_preorder = "pre.dat";
            ruta_inorder = "in.dat";
            pre_order_file.open(ruta_preorder, std::ios::out | std::ios::binary);
            in_order_file.open(ruta_inorder, std::ios::out | std::ios::binary);
            

            while(std::getline(file, word)){
                word += '\n';
                lineas_codificadas.push_back(word);
                for (auto character : word){
                    if (frecuencia_caracter.find(character) == frecuencia_caracter.end())
                        frecuencia_caracter[character] = 1;
                    else
                        frecuencia_caracter[character]++;
                    }

                }
                (lineas_codificadas.end()-1)->pop_back();
        }

        /**
         * @brief Construct a new Huffman Coding object
         * Si se usa este constructor es porque se quiere leer los datos de un archivo
         * @param ruta ruta del achivo comprimido
         * @param ruta_preorder parte de la llave para descomprimir. Se trata del arbol en preorder
         * @param ruta_inorder parte de la llave para descomprimir. Se trata del arbol en inorder
         */
        HuffmanCoding(std::string ruta, std::string ruta_preorder, std::string ruta_inorder) : ruta(ruta){
            this->ruta_preorder = ruta_preorder;
            this->ruta_inorder = ruta_inorder;

            _read_pre_order();
            _read_in_order();
            dictionary_tree = _buildTree(0, preorder_tree.size() - 1);

        }
        
        /**
         * @brief funcion para codificar el archivo
         * Toma la ruta especificada y se encarga de codificar el archivo
         * Los archivos generados se tratan de binarios
         * 
         */
        void enconde() { 
            struct MinHeapNode *left, *right, *top; 

            for (auto par : frecuencia_caracter)
                minHeap.push(new MinHeapNode(par.first, par.second, true)); 

            // Iterate while size of heap doesn't become 1 
            while (minHeap.size() != 1) { 

                // Extract the two minimum 
                // freq items from min heap 
                left = minHeap.top(); 
                minHeap.pop(); 

                right = minHeap.top(); 
                minHeap.pop(); 

                // Create a new internal node with 
                // frequency equal to the sum of the 
                // two nodes frequencies. Make the 
                // two extracted node as left and right children 
                // of this new node. Add this node 
                // to the min heap '$' is a special value 
                // for internal nodes, not used 
                top = new MinHeapNode('$', 
                                    left->freq + right->freq, false); 

                top->left = left; 
                top->right = right; 

                minHeap.push(top); 
            } 
            this->_store_pre_order();
            this->_store_in_order();
            pre_order_file.close();
            in_order_file.close();
            _write_file();


        }

        void decode(){
            //Cargamos el string
            std::string respuesta_en_bits;
            std::fstream file_comprimido;
            file_comprimido.open(ruta, std::ios::in | std::ios::binary);
            while (file_comprimido.peek() != EOF){
                std::bitset<128> chunk_respuesta(0);
                file_comprimido.read(reinterpret_cast<char*> (&chunk_respuesta), sizeof(std::bitset<128>));
                respuesta_en_bits += chunk_respuesta.to_string();
            }
            //Leemos el archivos para saber cuantos 0 no forman parte de la codificacion y son solo ruido
            std::fstream bits_muertos;
            bits_muertos.open("bits_muertos.dat", std::ios::in | std::ios::binary);
            bits_muertos.read(reinterpret_cast<char*>(&exceso_ultimo_chunk), sizeof(exceso_ultimo_chunk));
            bits_muertos.close();
            respuesta_en_bits = respuesta_en_bits.substr(0, respuesta_en_bits.length() - exceso_ultimo_chunk);

            std::string respuesta = "";
            MinHeapNode* busqueda_caracter = dictionary_tree;
            for (auto caracter : respuesta_en_bits){
                if (busqueda_caracter == nullptr){
                    std::cerr << "A ocurrido un error al leer el archivo.\n";
                    std::cerr << "Posible corrupcion del archivo comprimido o de las claves\n";
                    exit(1);
                }

                if (busqueda_caracter->nodo_caracter){
                    respuesta += busqueda_caracter->data;
                    busqueda_caracter = dictionary_tree;
                    
                }
                if (caracter == '1')
                    busqueda_caracter = busqueda_caracter->left;
                else
                    busqueda_caracter = busqueda_caracter->right;
                
            }
            std::ofstream decompressed_file;
            decompressed_file.open("decoded.txt");
            

            decompressed_file << respuesta;


        }


        private:
        /**
         * @brief funcion para guardar el recorrido en pre order
         * esta funcion desencadena las funciones recursivas del mismo nombre pero distinto parametros
         */
        void _store_pre_order() { 
            struct MinHeapNode* root = minHeap.top();
            std::string str;
            //dfs(root, "");
            if (!root) 
                return; 

            //Se guarda la cantidad de bits inutiles que se generan en el ultimo chunk
            pre_order_file.write(reinterpret_cast<char*> (&(root->data)), sizeof(root->data));
            pre_order_file.write(reinterpret_cast<char*> (&(root->freq)), sizeof(root->freq));
            pre_order_file.write(reinterpret_cast<char*> (&(root->nodo_caracter)), sizeof(root->nodo_caracter));



            if (root->nodo_caracter)
                symbols[root->data] = str;
             

            _store_pre_order(root->left, str + "1"); 
            _store_pre_order(root->right, str + "0"); 
        } 

        /**
         * @brief funcion para guardar el recorrido en pre order
         * 
         * @param root raiz del sub arbol a recorrer
         * @param str clave de huffman hasta el momento
         */
        void _store_pre_order(struct MinHeapNode* root, std::string str) { 

            if (!root) 
                return; 

            pre_order_file.write(reinterpret_cast<char*> (&(root->data)), sizeof(root->data));
            pre_order_file.write(reinterpret_cast<char*> (&(root->freq)), sizeof(root->freq));
            pre_order_file.write(reinterpret_cast<char*> (&(root->nodo_caracter)), sizeof(root->nodo_caracter));



            if (root->data != '$'){
                symbols[root->data] = str;
            } 

            _store_pre_order(root->left, str + "1"); 
            _store_pre_order(root->right, str + "0"); 
        } 

        /**
         * @brief Funcion encargada de leer los archivos binarios en pre_order
         * 
         */
        void _read_pre_order(){
            pre_order_file.close();
            pre_order_read.open(ruta_preorder, std::ios::in | std::ios::binary);


            while (pre_order_read.peek() != EOF){
                char answer_char;
                unsigned int answer_int;
                bool es_caracter;
                
                pre_order_read.read(reinterpret_cast<char*> (&answer_char), sizeof(char));
                pre_order_read.read(reinterpret_cast<char*> (&answer_int), sizeof(unsigned int));
                pre_order_read.read(reinterpret_cast<char*> (&es_caracter), sizeof(bool));


                MinHeapNode a(answer_char, answer_int, es_caracter);
                preorder_tree.push_back(a);
            }
        }
        /**
         * @brief funcion para guardar el recorrido en in order
         * esta funcion desencadena las funciones recursivas del mismo nombre pero distinto parametros
         */

        void _store_in_order() { 
            struct MinHeapNode* root = minHeap.top();
            std::string str;

            if (!root) 
                return; 
            

            if (root->nodo_caracter){
                symbols[root->data] = str;
            } 

            _store_in_order(root->left, str + "1"); 


            in_order_file.write(reinterpret_cast<char*> (&(root->data)), sizeof(root->data));
            in_order_file.write(reinterpret_cast<char*> (&(root->freq)), sizeof(root->freq));
            in_order_file.write(reinterpret_cast<char*> (&(root->nodo_caracter)), sizeof(root->nodo_caracter));

            _store_in_order(root->right, str + "0"); 
        } 

        /**
         * @brief funcion para guardar el recorrido en in order
         * 
         * @param root raiz del sub arbol a recorrer
         * @param str clave de huffman hasta el momento
         */

        void _store_in_order(struct MinHeapNode* root, std::string str) { 

            if (!root) 
                return; 

            if (root->data != '$'){
                symbols[root->data] = str;
            } 

            _store_in_order(root->left, str + "1"); 



            in_order_file.write(reinterpret_cast<char*> (&(root->data)), sizeof(root->data));
            in_order_file.write(reinterpret_cast<char*> (&(root->freq)), sizeof(root->freq));
            in_order_file.write(reinterpret_cast<char*> (&(root->nodo_caracter)), sizeof(root->nodo_caracter));

            _store_in_order(root->right, str + "0"); 
        } 
        /**
         * @brief Funcion encargada de leer los archivos binarios en in_order
         * 
         */

        void _read_in_order(){
            in_order_file.close();
            in_order_read.open(ruta_inorder, std::ios::in | std::ios::binary);


            while (in_order_read.peek() != EOF){
                char answer_char;
                unsigned int answer_int;
                bool es_caracter;
                in_order_read.read(reinterpret_cast<char*> (&answer_char), sizeof(char));
                in_order_read.read(reinterpret_cast<char*> (&answer_int), sizeof(unsigned int));
                in_order_read.read(reinterpret_cast<char*> (&es_caracter), sizeof(bool));
                
                MinHeapNode a(answer_char, answer_int, es_caracter);

                inorder_tree.push_back(a);


            }
        }




        /**
         * @brief codigo para leer dos arrays en inorder y preorder y reconstruir el arbol a partir de eso
         * Este codigo esta basado en un problema de leetcode y su respectiva solucion en geeks for geeks
         * El codigo fue adaptado para funcionar en el caso especifico del problema
         * tambien se quito argumentos y se adapto a una clase.
         * Función recursiva para construir un árbol binario de tamaño preorder_tree.size() a partir de la travesía Inorder 
         * y la travesía Preorder. Los valores iniciales de inStrt e inEnd deben ser 0 y preorder_tree.size() - 1. 
         * La función no realiza ninguna verificación de errores para casos en los que Inorder y Preorder no 
         * forman un árbol. Esta descripcion es una traduccion de la dada en geeks for geeks
         * @link https://www.geeksforgeeks.org/construct-tree-from-given-inorder-and-preorder-traversal/
         * @param inStrt comienzo del array
         * @param inEnd final del array
         * @return entrega la raiz del arbol que se construyo
         */

        int preIndex = 0; 
        MinHeapNode* _buildTree(int inStrt, int inEnd) 
        { 
        
            if (inStrt > inEnd) 
                return nullptr; 
        
            /* Pick current node from Preorder
            traversal using preIndex 
            and increment preIndex */
            MinHeapNode* tNode = new MinHeapNode(1,0, false); 
            *tNode = preorder_tree[preIndex++]; 

            /* If this node has no children then return */
            if (inStrt == inEnd) 
                return tNode; 
        
            /* Else find the index of this node in Inorder traversal */
            int inIndex = search(inorder_tree, inStrt, inEnd, *tNode); 
        
            /* Using index in Inorder traversal, construct left and 
            right subtress */
            tNode->left = _buildTree(inStrt, inIndex - 1); 
            tNode->right = _buildTree(inIndex + 1, inEnd); 
        
            return tNode; 
        } 
 

        /**
         * @brief funcion de utilidad para buscar en un array un valor especifico
         * Función para encontrar el índice del valor en arr[inicio...final]
         * La función asume que el valor está presente
         * @param arr el arreglo a buscar
         * @param strt comienzo del arreglo a buscar
         * @param end final del arreglo a buscar
         * @param value nodo buscado
         * @return int entrega el indice en que se encuentra el valor
         * @return entrega en caso de error el comienzo del array
         */
        int search(std::vector<MinHeapNode> arr, int strt, int end, MinHeapNode value) 
        { 
            int i; 
            for (i = strt; i <= end; i++) 
            { 
                if (arr[i] == value) 
                    return i; 
            } 
            return strt;
        } 
        /**
         * @brief Funcion para escribir el texto en un archivo binario. Genera la compresion.
         * 
         */
        void _write_file(){
            file.close();
            file.open("encoded.dat", std::ios::out | std::ios::binary);
            std::string respuesta = "";
            for (auto linea : lineas_codificadas){
                for (auto caracter : linea){
                    respuesta += symbols[caracter];
                }
            }

            for (int i = 0; i < respuesta.size(); i++){
                int contador = 0;  
                std::bitset<128> chunk_respuesta(0);
                while (contador < 128 && i < respuesta.size()){
                    bool answer = (respuesta[i] == '1')? true : false;
                    chunk_respuesta.set(128 - contador - 1, answer);
                    i++;
                    contador++;
                }
                i--;
                exceso_ultimo_chunk = 127 - contador; 
                file.write(reinterpret_cast<char*>(&chunk_respuesta), sizeof(chunk_respuesta));
            }
            std::fstream bits_muertos;
            bits_muertos.open("bits_muertos.dat", std::ios::out | std::ios::binary);
            bits_muertos.write(reinterpret_cast<char*>(&exceso_ultimo_chunk), sizeof(exceso_ultimo_chunk));
            bits_muertos.close();
            file.close();
        }
};
