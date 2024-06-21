#include <iostream>
#include "../Lempel_Ziv.h"
#include "../huffman.h"

int main(int argc, char* argv[]){
	HuffmanCoding codificador(argv[1]);
    	codificador.enconde();
	Lempel_ziv compresor(argv[1], std::stoi(argv[2]));
    	compresor.compress();
}
