import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import MaxNLocator
import sys
data = []
for line in sys.stdin:
    line = line.strip()
    if(line != ''):
        line = int(line)
        if(line < 15000 and line != 0):
            data.append(int(line))  # Parse numbers as they come from C++
# print(data[:10])  # Print first 10 numbers as an example

data = np.array(data)

plt.hist(data, bins=20, edgecolor='black')
plt.xlabel('Valor')
plt.ylabel('Frequência')
plt.title('Distribuição de Distâncias entre dois Vértices')
# plt.xscale('log')
# plt.yscale('log')

plt.gca().yaxis.set_major_locator(MaxNLocator(integer=True))

plt.savefig('./plots/distance_plot.png', format='png', dpi=300)
plt.close()