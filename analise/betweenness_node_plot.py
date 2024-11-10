import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import MaxNLocator, ScalarFormatter

path = 'node_betweenness'
data = np.loadtxt(path)

plt.hist(data, bins=20, edgecolor='black')
plt.xlabel('Valor')
plt.ylabel('Frequência')
plt.title('Distribuição de Betweenness dos Nós')
plt.yscale('log')

plt.gca().xaxis.set_major_formatter(ScalarFormatter(useMathText=True))
plt.ticklabel_format(style='sci', axis='x', scilimits=(0,0))

plt.savefig('./plots/node_betweenness_plot.png', format='png', dpi=300)
plt.close()