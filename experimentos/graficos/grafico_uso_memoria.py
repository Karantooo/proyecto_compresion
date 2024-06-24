import pandas as pd
import matplotlib.pyplot as plt 

df = pd.read_csv('../csv/uso_de_memoria.csv', sep=';')

df = df.sort_values(by='peso')

plt.figure()
funciones_unicas = df['Funcion'].unique()
for funcion in funciones_unicas:
    datos_funcion = df[df['Funcion'] == funcion]
    plt.plot(datos_funcion['peso']/(1024), datos_funcion['memoria ocupada en bytes']/(1024)**2, label=funcion, marker='.')
plt.title('Uso de memoria en bytes')
plt.xlabel('Peso del archivo (KB)')
plt.ylabel('Memoria ocupada (MB)')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()