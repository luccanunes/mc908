import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import MaxNLocator
import matplotlib.pyplot as plt

def plot_line_graph(points):

    # Separar os valores de x e y
    x_values = [point[0] for point in points]
    y_values = [point[1] for point in points]
    
    # Criar o gráfico de linha
    plt.plot(x_values, y_values, marker='', linestyle='-', color='b', label='Linha')
    
    # Configurações do gráfico
    # plt.title("Gráfico de Linha")
    plt.xlabel('Arcos removidos')
    plt.ylabel('Número de Componentes')
    plt.grid(True)
    plt.legend()
    
    plt.savefig('./edge_betweenness_plot.png', format='png', dpi=300)
    plt.close()

n = int(input())
pontos = []
for _ in range(n):
    a, b = input().split()
    pontos.append((int(a), int(b)))

plot_line_graph(pontos)


# path = 'clustering'
# data = np.loadtxt(path)

# plt.hist(data, bins=20, edgecolor='black')
# # plt.title('Distribuição dos Coeficientes de Clusterização')
# # plt.yscale('log')
