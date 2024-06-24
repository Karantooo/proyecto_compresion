#!/bin/bash

output_file="resultados_compresion_desscompresion.csv"

echo "size archivo;tiempo codificacion Huffman;tiempo compresion LZ;tiempo decodificacion Huffmann;tiempo decompresion LZ"
files=("../textos/texto_1mb.txt" "../textos/texto_750kb.txt" "../textos/texto_500kb.txt")

for ((c=1; c<=20; c++))
do
	for n in "${files[@]}"
	do
		./experimento_compresion.out $n 10
	done
done
