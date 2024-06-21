#include <iostream>
#include "../Lempel_Ziv.h"
#include "../huffman.h"

int main(int argc, char* argv[]){
	HuffmanCoding codificador(argv[1]);
    codificador.enconde();
}
