#!/bin/bash

output_file="resultados_compresion_desscompresion.csv"

echo "size archivo;tiempo codificacion Huffman;tiempo compresion LZ;tiempo decodificacion Huffmann;tiempo decompresion LZ"
files=("../textos/cancion.txt" "../textos/mio_cid.txt" "../textos/shakespeare.txt" "../textos/smash_wikipedia.txt" "../textos/texto.txt")

for ((c=1; c<=20; c++))
do
	for n in "${files[@]}"
	do
		./experimento_compresion $n 10
	done
done
