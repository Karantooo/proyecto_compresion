#pragma once
#include <iostream>

/**
 * @brief Este clase define un arbol utilizado para MinHeap
 * 
 */
struct MinHeapNode { 

	// One of the input characters 
	char data; 

	// Frequency of the character 
	unsigned int freq; 

	// Left and right child 
	MinHeapNode *left, *right; 
	bool nodo_caracter;


	MinHeapNode(char data, unsigned int freq, bool nodo_caracter) 

	{ 

		left = right = nullptr; 
		this->data = data; 
		this->freq = freq; 
		this->nodo_caracter = nodo_caracter;
	} 

    bool operator==(const MinHeapNode& otra) const {
        return ((this->data == otra.data) && (this->freq == otra.freq))? true : false;
    }
}; 

/**
 * @brief Comparador para Min HeapNode que los compara por frecuencia
 * 
 */
struct compare { 

	bool operator()(MinHeapNode* l, MinHeapNode* r) 

	{ 
		return (l->freq > r->freq); 
	} 
}; 

/**
 * @brief Funcion para poder imprimir por cout un MinHeapNode
 * 
 * @param stream 
 * @param nodo 
 * @return std::ostream& 
 */
std::ostream& operator<< (std::ostream& stream, MinHeapNode nodo){
    stream << nodo.data << " ";
    stream << nodo.freq;
    return stream;
}