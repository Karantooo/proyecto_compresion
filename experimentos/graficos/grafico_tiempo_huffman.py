import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('../csv/experimento_huffman.csv', sep=';')

df = df.sort_values(by='Tamano_archivo')

promedios = df.groupby('Tamano_archivo').mean()
desviaciones = df.groupby('Tamano_archivo').std()

plt.figure()
plt.errorbar(promedios.index/(1024**2), promedios['tiempo_codificacion'], yerr=desviaciones['tiempo_codificacion'], label='Tiempo Compresión Huffman', marker='o', linestyle='-' ,capsize=5)
plt.title('Tiempo de codificación Huffman por tamaño de archivo')
plt.xlabel('Tamaño archivo (MB)')
plt.ylabel('Tiempo (s)')
plt.grid(True)
plt.legend()
