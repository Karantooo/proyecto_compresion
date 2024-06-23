#!/bin/bash

# Imprimimos una cabecera para nuestro archivo CSV
output_file="resultados_memoria.csv"
echo "experimento;limite superior;memoria ocupada en bytes"
files=("../textos/cancion.txt" "../textos/mio_cid.txt" "../textos/shakespeare.txt" "../textos/smash_wikipedia.txt" "../textos/texto.txt")
for n in "${files[@]}"
do
	memoria1=$(valgrind ./experimento_compresion_memoria.cpp $n 10 | grep "total heap usage") >> $output_file
	memoria2=$(valgrind ./experimento_descompresion_memoria.cpp  $n 10 | grep "total heap usage") >> $output_file


done

