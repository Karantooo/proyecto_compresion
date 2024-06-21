#include <iostream>
#include <filesystem>

int main(int argc, char* argv[]){
	std::filesystem::path filename1 = argv[1];
	std::filesystem::path filename2 = argv[2];
	
	double filesize1 = std::filesystem::file_size(filename1.c_str());
	double filesize2 = std::filesystem::file_size(filename2.c_str());
	
	std::cout << filesize1 << " " << filesize2 << std::endl;
	double quotient;
	quotient = filesize1/filesize2;
	quotient = quotient*100;
	std::cout << "Porcentaje de compresion " << quotient << std::endl; 
}
