#include "Lempel_Ziv.h"

int main(){
    std::string texto = "Buenas tardes buenas dias tardes dias";
    std::string codificacion = Lempel_Ziv(texto);
    std::cout << texto << "\n\n" << codificacion << std::endl;
}