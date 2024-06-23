#!/bin/bash


echo "size archivo;tiempo codificacion Huffman"
files=("../textos/texto_1mb.txt" "../textos/texto_2mb.txt" "../textos/texto_3mb.txt" "../textos/texto_5mb.txt" "../textos/texto_10mb.txt")

for ((c=1; c<=20; c++))
do
	for n in "${files[@]}"
	do
		./experimento_tiempo_huffman.out $n
	done
done
