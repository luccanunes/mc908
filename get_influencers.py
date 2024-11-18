import os
import networkx as nx

# Lista de arquivos de saída dos algoritmos
algorithm_files = [
    'closeness_list.txt',
    'pagerankingrev_list.txt',
    'maxdegree_list.txt',
    # 'miranda_porto_list.txt',
]

# Função para ler os 10 melhores vértices de um arquivo
def read_top_vertices(filename, top_n=10):
    with open('./algoritmos/main-list/' + filename, 'r') as file:
        vertices = [line.strip() for line in file.readlines()[:top_n]]
    return vertices

# Dicionário para armazenar os 10 melhores vértices de cada algoritmo
top_vertices = {}

# Ler os 10 melhores vértices de cada arquivo
for algorithm_file in algorithm_files:
    algorithm_name = os.path.splitext(algorithm_file)[0]
    top_vertices[algorithm_name] = read_top_vertices(algorithm_file, 30)

# Encontrar a interseção dos 10 melhores vértices de todos os algoritmos
intersection = set(top_vertices[algorithm_files[0].split('.')[0]])
for algorithm_name in top_vertices:
    intersection &= set(top_vertices[algorithm_name])

# Carregar o grafo do arquivo .gexf
graph = nx.read_gexf('./redes/main-0.gexf')

# Buscar os labels dos vértices da interseção
intersection_labels = {vertex: graph.nodes[vertex]['label'] for vertex in intersection}

# Imprimir os resultados
print("Interseção dos 10 melhores vértices de todos os algoritmos (com labels):")
for vertex, label in intersection_labels.items():
    print(f"Vértice ID: {vertex}, Label: {label}")

# Se preferir, você pode salvar os resultados em um arquivo
with open('intersection_top_vertices_with_labels.txt', 'w') as outfile:
    outfile.write("Interseção dos 10 melhores vértices de todos os algoritmos (com labels):\n")
    for vertex, label in intersection_labels.items():
        outfile.write(f"Vértice ID: {vertex}, Label: {label}\n")