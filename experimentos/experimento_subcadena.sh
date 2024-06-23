#!/bin/bash

output_file="resultados_subcadena.csv"

echo "size subcadena;tiempo compresion LZ;tiempo descompresion LZ"

for(( c = 1; c <= 20; c++))
do
	for n in 5 10 15 20
	do
		./experimento_compresion_LZ.out "../textos/mio_cid.txt" $n
	done
done
