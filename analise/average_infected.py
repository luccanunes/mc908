import pandas as pd
import matplotlib.pyplot as plt

# Ler os dados do arquivo CSV
# df = pd.read_csv('../simulador/algorithm_curves_50steps_23min.csv')
df = pd.read_csv('../simulador/algorithm_curves.csv')

# Plotar o gráfico de curvas
plt.figure(figsize=(10, 6))
for alg in df['Algorithm'].unique():
    subset = df[df['Algorithm'] == alg]
    plt.plot(subset['InitialInfected'], subset['AverageInfected'], label=alg)

plt.xlabel('Tamanho do Conjunto Inicial de Infectados')
plt.ylabel('Quantidade Total de Infectados')
plt.title('Curvas de Propagação de Influência por Algoritmo: 1 passo')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig('algorithm_curves.png')
plt.show()