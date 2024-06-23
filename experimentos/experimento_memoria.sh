#!/bin/bash

# Imprimimos una cabecera para nuestro archivo CSV
output_file="resultados_memoria.csv"
echo "Funcion;archivo;peso;memoria ocupada en bytes"
files=("../textos/cancion.txt" "../textos/mio_cid.txt" "../textos/shakespeare.txt" "../textos/smash_wikipedia.txt" "../textos/texto.txt" "../textos/texto_1mb.txt")

for n in "${files[@]}"
do
	tamanio_archivo=$(stat -c %s $n)

	memoria1=$(valgrind ./compresion_huffman.out $n 2>&1 | grep "total heap usage") 
	memoria2=$(valgrind ./descompresion_huffman.out encoded.dat pre.dat in.dat 2>&1 | grep "total heap usage") 
	
	memoria3=$(valgrind ./compresion_lz.out $n 2>&1 | grep "total heap usage")
	memoria4=$(valgrind ./descompresion_lz.out LZ_compression.dat 2>&1 | grep "total heap usage")
	
	echo "Codificacion huffman;$n;$tamanio_archivo;$memoria1"
	echo "Descodificacion huffman;$n;$tamanio_archivo;$memoria2"

	echo "Compresion lz;$n;$tamanio_archivo;$memoria3"
	echo "Descompresion lz;$n;$tamanio_archivo;$memoria4"


done

