#include <iostream>
#include "../Lempel_Ziv.h"
#include "../huffman.h"

int main(int argc, char* argv[]){
	Lempel_ziv compresor(argv[1], 15);
    	compresor.compress();
}
