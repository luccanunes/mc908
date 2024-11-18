import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import MaxNLocator
import matplotlib.pyplot as plt

def plot_line_graph(points):

    # Separar os valores de x e y
    x_values = [point[0] for point in points]
    y_values = [point[1] for point in points]
    
    # Criar o gráfico de linha
    plt.plot(x_values, y_values, marker='', linestyle='-', color='b')
    
    # Configurações do gráfico
    plt.xlabel('Nós removidos')
    plt.ylabel('Número de Componentes')
    plt.grid(True)
    
    plt.savefig('./node_betweenness_plot.png', format='png', dpi=300)
    plt.close()

n = int(input())
pontos = []
for _ in range(n):
    a, b = input().split()
    pontos.append((int(a), int(b)))

plot_line_graph(pontos)