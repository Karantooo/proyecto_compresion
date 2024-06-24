#ifndef TRIE_H
#define TRIE_H

#include <vector>

const int CHARACTER_NUMBER = 256;

/**
 * @brief Clase para crear un trie
 * Este trie esta hecho para aplicar LZ. Es una implementacion para un trie que considera
 * los caracteres de la tabla ASCII.
 * Esta clase esta basado en un codigo de geeks for geeks
 * @link https://www.geeksforgeeks.org/trie-insert-and-search/
 */
struct TrieNode {

    // pointer array for child nodes of each node
    TrieNode* childNode[CHARACTER_NUMBER];

    // Used for indicating ending of string
    bool wordEnd;
    int begin;
    unsigned char module;

    /**
     * @brief Construye un nuevo trie
     * inicializa wordEnd a falso
     * el index de childnode lo inicializa con nullptr
     * 
     */
    TrieNode(){

        wordEnd = false;
        for (int i = 0; i < CHARACTER_NUMBER; i++) {
            childNode[i] = NULL;
        }
    }

    /**
     * @brief Constructor
     * Inicializa la variable wordEnd con falso
     * Establece el índice de inicio y fin en el mensaje de la palabra que termina con el carácter actual representado por este nodo.
     * Inicializa cada índice del arreglo childNode con NULL
     */

    TrieNode(int begin, unsigned char module) : begin(begin), module(module)
    {
        wordEnd = false;
        for (int i = 0; i < CHARACTER_NUMBER; i++) {
            childNode[i] = NULL;
        }
    }
};


/**
 * @brief Inserta caracter a un trie
 * 
 * @param root 
 * @param key 
 * @param begin 
 */
void insert_key(TrieNode* root, std::string key, int begin)
{
    // Initialize the currentNode pointer with the root node and the end index of the word.
    unsigned char tmp_char;
    TrieNode* currentNode = root;
    unsigned char module = 0;

    // Iterate across the length of the string
    for (auto c : key) {
        module++;
        tmp_char = static_cast<unsigned char>(c);
        // Check if the node exist for the current
        // character in the Trie.
        if (currentNode->childNode[tmp_char] == NULL) {

            // If node for current character does not exist
            // then make a new node
            TrieNode* newNode = new TrieNode();

            // Keep the reference for the newly created
            // node.
            currentNode->childNode[tmp_char] = newNode;
           
            
        }

        // Now, move the current node pointer to the newly
        // created node.
        
        currentNode = currentNode->childNode[tmp_char];
    }

    // Increment the wordEndCount for the last currentNode
    // pointer this implies that there is a string ending at
    // currentNode and set the begin and end index of the word.

    currentNode->wordEnd = true;
    currentNode->begin = begin;
    currentNode->module = module;
}

/**
 * @brief Busca caracter en un trie
 * 
 * @param root 
 * @param key 
 * @return std::pair<int, int>* 
 */
std::pair<int, unsigned char>* search_key(TrieNode* root, std::string key)
{
    unsigned char tmp_char;
    // Initialize the currentNode pointer with the root node, the pair that will be returned and a bool value to verify if the word is only a character
    TrieNode* currentNode = root;
    std::pair<int, unsigned char>* word_index_range = new std::pair<int, unsigned char>();

    // Iterate across the length of the string
    for (auto c : key) {

        // Check if the node exist for the current
        // character in the Trie.
        tmp_char = static_cast<unsigned char>(c);
        if (currentNode->childNode[tmp_char] == nullptr) {

            // Given word does not exist in Trie
            return nullptr;
        }

        // Move the currentNode pointer to the already
        // existing node for current character.
        
        currentNode = currentNode->childNode[tmp_char];
    }

    // If the final character of key is the final of a word, returns begin and end index, if not return a nullptr
    if(currentNode->wordEnd == true){
        word_index_range->first = currentNode->begin;
        word_index_range->second = currentNode->module;
        return word_index_range;
    }else{
        return nullptr;
    }
}

#endif
