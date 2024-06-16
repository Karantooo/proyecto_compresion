#ifndef TRIE_H
#define TRIE_H

#include <bits/stdc++.h>

const int CHARACTER_NUMBER = 256;

/**
 * @brief 
 * 
 */
struct TrieNode {

    // pointer array for child nodes of each node
    TrieNode* childNode[CHARACTER_NUMBER];

    // Used for indicating ending of string
    bool wordEnd;
    unsigned long begin;
    unsigned long end;

    TrieNode(){
        // constructor
        // initialize the wordEnd variable with false
        // initialize every index of childNode array with
        // NULL
        wordEnd = false;
        for (int i = 0; i < CHARACTER_NUMBER; i++) {
            childNode[i] = NULL;
        }
    }
    TrieNode(unsigned long begin, unsigned long end) : begin(begin), end(end)
    {
        // constructor
        // initialize the wordEnd variable with false
        // set the begin and the end index in the message of the word that finishes with the current character representated by this node.
        // initialize every index of childNode array with
        // NULL
        wordEnd = false;
        for (int i = 0; i < CHARACTER_NUMBER; i++) {
            childNode[i] = NULL;
        }
    }
};


/**
 * @brief 
 * 
 * @param root 
 * @param key 
 * @param begin 
 */
void insert_key(TrieNode* root, std::string key, unsigned long begin)
{
    // Initialize the currentNode pointer with the root node and the end index of the word.
    unsigned char tmp_char;
    TrieNode* currentNode = root;
    int end = begin - 1;

    // Iterate across the length of the string
    for (auto c : key) {
        end++;
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
    currentNode->end = end;
}

/**
 * @brief 
 * 
 * @param root 
 * @param key 
 * @return std::pair<int, int>* 
 */
std::pair<unsigned long, unsigned long>* search_key(TrieNode* root, std::string key)
{
    unsigned char tmp_char;
    // Initialize the currentNode pointer with the root node, the pair that will be returned and a bool value to verify if the word is only a character
    TrieNode* currentNode = root;
    std::pair<unsigned long, unsigned long>* word_index_range = new std::pair<unsigned long, unsigned long>();

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
        word_index_range->second = currentNode->end;
        return word_index_range;
    }else{
        return nullptr;
    }
}

#endif
