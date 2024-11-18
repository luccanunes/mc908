import numpy as np
from scipy.cluster.hierarchy import dendrogram
import matplotlib.pyplot as plt
import sys

sys.setrecursionlimit(40000)

Z = []

n = int(input())
for i in range(n):
    a, b, c, d = input().split()
    Z.append([int(a), int(b), float(int(c)), int(d)])

Z = np.array(Z)

# Plotando o dendrograma
plt.figure(figsize=(20, 5))
dendrogram(Z, p = 200, truncate_mode = 'lastp')

plt.title("Dendrograma com Componentes Separados")
plt.xlabel("Grupos")
plt.ylabel("Quantidade de Vértices")

plt.savefig('./result.png', format='png', dpi=300)
plt.close()
