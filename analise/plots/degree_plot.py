import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import MaxNLocator, ScalarFormatter

path = 'degree_in'
data = np.loadtxt(path)

plt.hist(data, bins=20, edgecolor='black')
plt.xlabel('Valor')
plt.ylabel('Frequência')
plt.title('Distribuição de Graus de Entrada dos Nós')
plt.yscale('log')

plt.savefig('./plots/degree_in_plot.png', format='png', dpi=300)
plt.close()

path = 'degree_out'
data = np.loadtxt(path)

plt.hist(data, bins=20, edgecolor='black')
plt.xlabel('Valor')
plt.ylabel('Frequência')
plt.title('Distribuição de Graus de Saída dos Nós')
plt.yscale('log')

plt.savefig('./plots/degree_out_plot.png', format='png', dpi=300)
plt.close()