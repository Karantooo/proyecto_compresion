#!/bin/bash

# Imprimimos una cabecera para nuestro archivo CSV
echo "experimento;limite superior;memoria ocupada en bytes"
files = ("cancion.txt", "mio_cid.txt", "shakespeare.txt", "smash_wikipedia.txt", "texto.txt")
for n in "${files[@]}"
do
	memoria1 = $(valgrind ./experimento_compresion_memoria.cpp "$n" 20 | grep "total heap usage")
	memoria2 = $(valgrind ./experimento_descompresion_memoria.cpp  "$n" 20 | grep "total heap usage")

done

