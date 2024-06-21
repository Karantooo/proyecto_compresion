#include <iostream>
#include "../Lempel_Ziv.h"
#include "../huffman.h"

int main(int argc, char* argv[]){
	HuffmanCoding decodificador(argv[1]);
    	decodificador.decode();
	Lempel_ziv descompresor(argv[1], std::stoi(argv[2]));
    	compresor.decompress();
}
