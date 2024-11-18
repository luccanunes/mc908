import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import MaxNLocator

path = 'clustering'
data = np.loadtxt(path)

plt.hist(data, bins=20, edgecolor='black')
plt.xlabel('Valor')
plt.ylabel('Frequência')
plt.title('Distribuição dos Coeficientes de Clusterização')
plt.yscale('log')

plt.savefig('./plots/clustering_plot.png', format='png', dpi=300)
plt.close()