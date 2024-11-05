import networkx as nx
import argparse

# Configurar o analisador de argumentos
parser = argparse.ArgumentParser(description='Converter um arquivo .gexf para um arquivo de texto com uma lista de arestas usando IDs numéricos 0-indexados.')
parser.add_argument('input_file', type=str, help='O arquivo .gexf de entrada')
parser.add_argument('output_file', type=str, help='O arquivo de texto de saída')

# Analisar os argumentos
args = parser.parse_args()

# Carregar o grafo do arquivo .gexf
G = nx.read_gexf(args.input_file)

# Mapear IDs de string para IDs numéricos 0-indexados
id_mapping = {node: idx for idx, node in enumerate(G.nodes())}

# Criar um novo grafo com IDs numéricos
H = nx.Graph()
for u, v in G.edges():
    H.add_edge(id_mapping[u], id_mapping[v])

# Obter o número de vértices e arestas
num_vertices = H.number_of_nodes()
num_edges = H.number_of_edges()

# Salvar o novo grafo em um arquivo de texto com uma lista de arestas
with open(args.output_file, 'w') as f:
    # Escrever o número de vértices e arestas na primeira linha
    f.write(f"{num_vertices} {num_edges}\n")
    # Escrever as arestas
    for u, v in H.edges():
        f.write(f"{u} {v}\n")