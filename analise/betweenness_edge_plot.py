import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import MaxNLocator, ScalarFormatter

path = 'edge_betweenness'
data = np.loadtxt(path)

plt.hist(data, bins=20, edgecolor='black')
plt.xlabel('Valor')
plt.ylabel('Frequência')
plt.title('Distribuição de Betweenness das Arestas')
plt.yscale('log')

plt.gca().xaxis.set_major_formatter(ScalarFormatter(useMathText=True))
plt.ticklabel_format(style='sci', axis='x', scilimits=(0,0))

plt.savefig('./plots/edge_betweenness_plot.png', format='png', dpi=300)
plt.close()