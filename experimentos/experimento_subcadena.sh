#!/bin/bash

for(( c = 1; c <= 20; c++)
do
	for n in 10 20 30 40 50
	do
		./experimento_compresion_LZ "shakespeare.txt" $n
	done
done
