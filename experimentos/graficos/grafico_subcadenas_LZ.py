import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('../csv/experimento_subcadena.csv', sep=';')

promedios = df.groupby('size subcadena').mean()
desviaciones = df.groupby('size subcadena').std()

plt.figure()
plt.errorbar(promedios.index, promedios['tiempo compresion LZ'], yerr=desviaciones['tiempo compresion LZ'] , label='Tiempo Compresión LZ', marker='o', linestyle='-' ,capsize=5)
plt.errorbar(promedios.index, promedios['tiempo descompresion LZ'], yerr=desviaciones['tiempo descompresion LZ'] ,label='Tiempo Descompresión LZ', marker='x', linestyle='-' ,capsize=5 )
plt.title('Tiempos de Compresión y Descompresión LZ por Tamaño de Subcadena')
plt.xlabel('Tamaño de Subcadena (número entero)')
plt.ylabel('Tiempo (s)')
plt.grid(True)
plt.legend()

plt.figure()
plt.errorbar(promedios.index, promedios['porcentaje compresion LZ'], yerr=desviaciones['porcentaje compresion LZ'] , label='Porcentaje Compresión LZ', marker='o', linestyle='-' ,capsize=5)
plt.title('Porcentaje de compresión LZ por tamaño de subcadena')
plt.xlabel('Tamaño de subcadena (número entero)')
plt.ylabel('Tamaño respecto al original (porcentaje)')
plt.grid(True)
plt.legend()

plt.show()