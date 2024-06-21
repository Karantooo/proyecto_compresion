#!/bin/bash

# Imprimimos una cabecera para nuestro archivo CSV
echo "experimento;limite superior;memoria ocupada en bytes"

palabra=$(valgrind ./experimento_compresion "$n" 2>&1 | grep "total heap usage")
palabra=$(valgrind ./experimento_descompresion "$n" 2>&1 | grep "total heap usage")

