#pragma once
#include <unordered_map>
#include <string>
#include <queue>
#include <fstream>
#include <iostream>
/**
 * @brief archivo que tiene la implementacion de huffman 
 * Este archivo esta basado en el codigo disponible en geeks for geeks haciendo modificaciones.
 * @link https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
 */



struct MinHeapNode { 

	// One of the input characters 
	char data; 

	// Frequency of the character 
	unsigned freq; 

	// Left and right child 
	MinHeapNode *left, *right; 

	MinHeapNode(char data, unsigned freq) 

	{ 

		left = right = NULL; 
		this->data = data; 
		this->freq = freq; 
	} 
}; 


struct compare { 

	bool operator()(MinHeapNode* l, MinHeapNode* r) 

	{ 
		return (l->freq > r->freq); 
	} 
}; 


class HuffmanCoding{
    private:
        std::unordered_map<char, int> frecuencia_caracter;
        std::unordered_map<char, std::string> symbols;
        std::ifstream file;
        std::priority_queue<MinHeapNode*, std::vector<MinHeapNode*>, 
            compare> minHeap; 
        
    public:

        HuffmanCoding(std::string ruta){
            file.open(ruta);
            std::string word;

            while(std::getline(file, word)){
                std::cout << word << std::endl;
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
        }

        void printCodes() { 
            struct MinHeapNode* root = minHeap.top();
            std::string str;

            if (!root) 
                return; 

            if (root->data != '$'){
                std::cout << root->data << ": " << str << "\n"; 
                symbols[root->data] = str;
            } 

            printCodes(root->left, str + "1"); 
            printCodes(root->right, str + "0"); 
        } 


        void printCodes(struct MinHeapNode* root, std::string str) { 

            if (!root) 
                return; 

            if (root->data != '$'){
                std::cout << root->data << ": " << str << "\n"; 
                symbols[root->data] = str;
            } 

            printCodes(root->left, str + "1"); 
            printCodes(root->right, str + "0"); 
        } 
};



