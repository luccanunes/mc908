import networkx as nx
import argparse

# Configurar o analisador de argumentos
parser = argparse.ArgumentParser(description='Converter um arquivo .gexf para um arquivo de texto com uma lista de arestas usando IDs numéricos 0-indexados.')
parser.add_argument('input_file', type=str, help='O arquivo .gexf de entrada')
# parser.add_argument('output_file', type=str, help='O arquivo de texto de saída')
# parser.add_argument('output_gexf_file', type=str, help='O novo arquivo .gexf de saída com os vértices renomeados')

args = parser.parse_args()
G = nx.read_gexf(args.input_file)

H = nx.DiGraph()
for u, v in G.edges():
    H.add_edge(u, v)

dc = nx.clustering(H)

vec = []
tot = 0

for a in dc:
    vec.append(dc[a])
    tot += dc[a]

vec = sorted(vec)
print(vec)
print(tot / len(vec))