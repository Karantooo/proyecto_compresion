#pragma once
#include <unordered_map>
#include <string>
#include <queue>
#include <fstream>
#include <iostream>
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
        std::ifstream file;
        std::priority_queue<MinHeapNode*, std::vector<MinHeapNode*>, 
            compare> minHeap; 
        std::fstream pre_order_file, in_order_file;
        std::fstream pre_order_read, in_order_read;
        std::string ruta;

        std::vector<MinHeapNode> preorder_tree;
        std::vector<MinHeapNode> inorder_tree;


        
    public:

        HuffmanCoding(std::string ruta): ruta(ruta){
            file.open(ruta);
            std::string word;
            pre_order_file.open("pre_" + ruta + ".dat", std::ios::out | std::ios::binary);
            in_order_file.open("in_" + ruta + ".dat", std::ios::out | std::ios::binary);
            



            while(std::getline(file, word)){
                // std::cout << word << std::endl;
                for (auto character : word){
                    if (frecuencia_caracter.find(character) == frecuencia_caracter.end())
                        frecuencia_caracter[character] = 1;
                    else
                        frecuencia_caracter[character]++;
                    }
                }
        }
        

        void enconde() { 
            struct MinHeapNode *left, *right, *top; 

            for (auto par : frecuencia_caracter)
                minHeap.push(new MinHeapNode(par.first, par.second)); 

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
                                    left->freq + right->freq); 

                top->left = left; 
                top->right = right; 

                minHeap.push(top); 
            } 
            this->_store_pre_order();
            this->_store_in_order();

        }


        private:

        void _store_pre_order() { 
            struct MinHeapNode* root = minHeap.top();
            std::string str;

            if (!root) 
                return; 
            
            pre_order_file.write(reinterpret_cast<char*> (&(*root)), sizeof(MinHeapNode));


            if (root->data != '$'){
                symbols[root->data] = str;
            } 

            _store_pre_order(root->left, str + "1"); 
            _store_pre_order(root->right, str + "0"); 
        } 


        void _store_pre_order(struct MinHeapNode* root, std::string str) { 

            if (!root) 
                return; 

            pre_order_file.write(reinterpret_cast<char*> (&(*root)), sizeof(MinHeapNode));
            


            if (root->data != '$'){
                symbols[root->data] = str;
            } 

            _store_pre_order(root->left, str + "1"); 
            _store_pre_order(root->right, str + "0"); 
        } 

        void _read_pre_order(){
            pre_order_file.close();
            pre_order_read.open("pre_" + ruta + ".dat", std::ios::in | std::ios::binary);


            while (pre_order_read.peek() != EOF){
                MinHeapNode a('a', 0);
                pre_order_read.read(reinterpret_cast<char*> (&a), sizeof(MinHeapNode));
                preorder_tree.push_back(a);
                std::cout << a << std::endl;
            }
        }

        void _store_in_order() { 
            struct MinHeapNode* root = minHeap.top();
            std::string str;

            if (!root) 
                return; 
            
            in_order_file.write(reinterpret_cast<char*> (&(*root)), sizeof(MinHeapNode));


            if (root->data != '$'){
                symbols[root->data] = str;
            } 

            _store_in_order(root->left, str + "1"); 
            _store_in_order(root->right, str + "0"); 
        } 


        void _store_in_order(struct MinHeapNode* root, std::string str) { 

            if (!root) 
                return; 

            


            if (root->data != '$'){
                symbols[root->data] = str;
            } 

            _store_in_order(root->left, str + "1"); 
            in_order_file.write(reinterpret_cast<char*> (&(*root)), sizeof(MinHeapNode));
            _store_in_order(root->right, str + "0"); 
        } 

        void _read_in_order(){
            in_order_file.close();
            in_order_read.open("in_" + ruta + ".dat", std::ios::in | std::ios::binary);


            while (in_order_read.peek() != EOF){
                MinHeapNode a('a', 0);
                in_order_read.read(reinterpret_cast<char*> (&a), sizeof(MinHeapNode));
                inorder_tree.push_back(a);
            }
        }


};



