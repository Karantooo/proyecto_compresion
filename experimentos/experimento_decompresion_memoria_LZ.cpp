#include <iostream>
#include "../Lempel_Ziv.h"
#include "../huffman.h"

int main(int argc, char* argv[]){
	Lempel_ziv descompresor(argv[1]);
    descompresor.decompress();

    return 0;
}

