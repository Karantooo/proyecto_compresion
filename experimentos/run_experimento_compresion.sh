#!/bin/bash
echo "size archivo 1;tiempo codicicacion Huffmann;size archivo 2;tiempo compresion LZ"
files=("../textos/cancion.txt" "../textos/mio_cid.txt" "../textos/shakespeare.txt" "../textos/smash_wikipedia.txt" "../textos/texto.txt")

for ((c=1; c<=20; c++))
do
	for n in "${files[@]}"
	do
		./experimento_compresion.out "$n" 10
	done
done
