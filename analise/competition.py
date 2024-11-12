import pandas as pd
import matplotlib.pyplot as plt

# Ler os dados dos arquivos CSV
general_results = pd.read_csv('../simulador/competition_results_general.csv')
pairwise_results = pd.read_csv('../simulador/competition_results_pairwise.csv')

# Plotar o número de vitórias
plt.figure(figsize=(10, 5))
plt.bar(general_results['Algorithm'], general_results['Wins'], color='skyblue')
plt.xlabel('Algoritmos')
plt.ylabel('Número de Vitórias')
plt.title('Número de Vitórias por Algoritmo')
plt.xticks(rotation=45)
plt.tight_layout()
plt.savefig('wins_by_algorithm.png')
plt.show()

# Plotar a média de infecções por algoritmo
plt.figure(figsize=(10, 5))
plt.bar(general_results['Algorithm'], general_results['AverageInfected'], color='lightgreen')
plt.xlabel('Algoritmos')
plt.ylabel('Média de Vértices Infectados')
plt.title('Média de Vértices Infectados por Algoritmo')
plt.xticks(rotation=45)
plt.tight_layout()
plt.savefig('average_infected_by_algorithm.png')
plt.show()

# Plotar as vitórias por par de algoritmos
plt.figure(figsize=(10, 5))
for i, row in pairwise_results.iterrows():
    plt.bar(f"{row['Algorithm1']} vs {row['Algorithm2']}", row['Wins1'], color='red')
    plt.bar(f"{row['Algorithm1']} vs {row['Algorithm2']}", row['Wins2'], bottom=row['Wins1'], color='blue')
plt.xlabel('Pares de Algoritmos')
plt.ylabel('Número de Vitórias')
plt.title('Número de Vitórias por Par de Algoritmos')
plt.xticks(rotation=45)
plt.tight_layout()
plt.savefig('wins_by_pair.png')
plt.show()

# Plotar as médias de infecções por par de algoritmos
plt.figure(figsize=(10, 5))
for i, row in pairwise_results.iterrows():
    plt.bar(f"{row['Algorithm1']} vs {row['Algorithm2']}", row['AverageInfected1'], color='red')
    plt.bar(f"{row['Algorithm1']} vs {row['Algorithm2']}", row['AverageInfected2'], bottom=row['AverageInfected1'], color='blue')
plt.xlabel('Pares de Algoritmos')
plt.ylabel('Média de Infecções')
plt.title('Média de Infecções por Par de Algoritmos')
plt.xticks(rotation=45)
plt.tight_layout()
plt.savefig('infections_by_pair.png')
plt.show()