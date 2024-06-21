#!/bin/bash
echo "experimento codifi
files = ("cancion.txt", "mio_cid.txt", "shakespeare.txt", "smash_wikipedia.txt", "texto.txt")

for (c = 1; c <= 20; c++)
do
	for n in "${files[@]}"
	do
		./experimento_compresion.cpp "$n" 20
	done
done
