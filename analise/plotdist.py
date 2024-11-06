import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import MaxNLocator

path = 'distance'
data = np.loadtxt(path)

plt.hist(data, bins=20, edgecolor='black')
plt.xlabel('Valor')
plt.ylabel('Frequência')
plt.title('Distribuição de Distâncias entre dois Vértices')
plt.gca().yaxis.set_major_locator(MaxNLocator(integer=True))

plt.savefig('./plots/distance_plot.png', format='png', dpi=300)
plt.close()