#include <iostream>
#include "../Lempel_Ziv.h"
#include "../huffman.h"

int main(int argc, char* argv[]){
	HuffmanCoding decodificador(argv[1], argv[2], argv[3]);
    decodificador.decode();
    return 0;
}