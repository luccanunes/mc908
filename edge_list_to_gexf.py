import networkx as nx

def convert_to_gexf(input_file, output_file):
    # Cria um grafo direcionado
    G = nx.MultiDiGraph()

    # Lê o arquivo de entrada
    with open(input_file, 'r') as f:
        lines = f.readlines()
        n, m = map(int, lines[0].strip().split())
        
        # Adiciona os vértices
        for i in range(n):
            G.add_node(i)
        
        # Adiciona as arestas
        for line in lines[1:]:
            a, b = map(int, line.strip().split())
            G.add_edge(a, b)
    
    # Escreve o grafo no formato GEXF
    nx.write_gexf(G, output_file)
    print(f"Grafo salvo em {output_file}")

# Exemplo de uso
input_file = './redes/15.txt'  # Substitua pelo caminho do seu arquivo de entrada
output_file = './redes/15.gexf'  # Substitua pelo caminho do seu arquivo de saída
convert_to_gexf(input_file, output_file)