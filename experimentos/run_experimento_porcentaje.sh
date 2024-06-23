#!/bin/bash

echo "size archivo;porcentaje codificacion;porcentaje compresion"

files=("../textos/cancion.txt" "../textos/mio_cid.txt" "../textos/shakespeare.txt" "../textos/smash_wikipedia.txt" "../textos/texto.txt" "../textos/texto_1mb.txt" "../textos/texto_2mb.txt" "../textos/texto_3mb.txt" "../textos/texto_5mb.txt" "../textos/texto_10mb.txt")

for ((c=1; c<=20; c++))
do
	for n in "${files[@]}"
	do
		./experimento_porcentaje.out $n 10
	done
done

