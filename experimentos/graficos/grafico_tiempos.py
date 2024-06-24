import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('../csv/experimento_tiempos.csv', sep=';')

df = df.sort_values(by='size archivo')
promedios = df.groupby('size archivo').mean()
desviaciones = df.groupby('size archivo').std()
x = promedios.index/(1024)

plt.figure()
plt.errorbar(x, promedios['tiempo codificacion Huffman'], yerr=desviaciones['tiempo codificacion Huffman'], label='Codificación Huffman', marker='.', linestyle='-', capsize=5)
plt.errorbar(x, promedios['tiempo compresion LZ'], yerr=desviaciones['tiempo compresion LZ'], label='Compresión LZ', marker='.', linestyle='-', capsize=5)
plt.title('Tiempos codificación y compresión según tamaño de archivo')
plt.xlabel('Tamaño archivo (KB)')
plt.ylabel('Tiempo (s)')
plt.grid(True)
plt.legend()

plt.figure()
plt.errorbar(x, promedios['tiempo decodificacion Huffman'], yerr=desviaciones['tiempo decodificacion Huffman'], label='Decodificación Huffman', marker='.', linestyle='-', capsize=5)
plt.errorbar(x, promedios['tiempo descompresion LZ'], yerr=desviaciones['tiempo descompresion LZ'], label='Descompresión LZ', marker='.', linestyle='-', capsize=5)
plt.title('Tiempos decodificación y descompresión según tamaño de archivo')
plt.xlabel('Tamaño archivo (KB)')
plt.ylabel('Tiempo (s)')
plt.grid(True)
plt.legend()
plt.show()