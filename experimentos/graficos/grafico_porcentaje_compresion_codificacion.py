import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('../csv/experimento_porcentaje.csv', sep=';')

x = df['size archivo']/(1024**2)
y1 = df['porcentaje codificacion']
y2 = df['porcentaje compresion']

plt.figure()
plt.plot(x, y1, label='Porcentaje de codificación', marker='.')
plt.plot(x, y2, label='Porcentaje de compresión', marker='.')
plt.title('Porcentaje de codificación y compresión según tamaño del archivo')
plt.xlabel('Tamaño del archivo (MB)')
plt.ylabel('Tamaño respecto al original (porcentaje)')
plt.legend()
plt.show()