import numpy as np
from scipy.cluster.hierarchy import dendrogram
import matplotlib.pyplot as plt
import sys

# Increase the recursion limit to a higher value
sys.setrecursionlimit(40000)  # You can adjust this number as needed

# A matriz de ligação Z deve ter índices únicos para novos clusters.
# Índices 0, 1, 2, 3, 4 e 5 representam os nós iniciais individuais.
# A partir do índice 6, representamos novos clusters formados pelas uniões.

Z = []

n = int(input())
for i in range(n):
    a, b, c, d = input().split()
    Z.append([int(a), int(b), float(c), int(d)])

Z = np.array(Z)

# Os índices dos novos clusters (6, 7, 8, etc.) devem ser únicos e aumentam conforme
# unimos os clusters anteriores.

# Plotando o dendrograma
plt.figure(figsize=(10, 6))
dendrogram(Z)
plt.title("Dendrograma com Componentes Separados")
plt.xlabel("Grupos")
plt.ylabel("Quantidade de Vértices")

plt.savefig('./result.png', format='png', dpi=300)
plt.close()
