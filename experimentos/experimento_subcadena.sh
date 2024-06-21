#!/bin/bash

for( c = 1; c <= 20; c++)
do
	for n in 5 10 15 20 25 30
	do
		./experimento_compresion_LZ.cpp "shakespeare.txt" $n
	done
done
