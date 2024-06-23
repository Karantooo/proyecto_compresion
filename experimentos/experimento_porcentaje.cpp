#include <iostream>
#include <filesystem>
#include "../huffman.h"
#include "../Lempel_Ziv.h"

int main(int argc, char* argv[]){
	std::filesystem::path filename1 = argv[1];	
	double filesize1 = std::filesystem::file_size(filename1.c_str());
	
	HuffmanCoding codificador(filename1);
    	codificador.enconde();
	std::filesystem::path f_codificado = "encoded.dat";
	double codificado = std::filesystem::file_size(f_codificado.c_str());	
	double quotient1 = (codificado / filesize1) * 100;

	Lempel_ziv compresor(filename1, 10);
	compresor.compress();
	std::filesystem::path f_comprimido = "LZ_compression.dat";
        double comprimido = std::filesystem::file_size(f_comprimido.c_str());
        double quotient2 = (comprimido / filesize1) * 100;
	
	std::cout << filesize1 << ";" << quotient1 << ";" << quotient2 << std::endl; 
}
