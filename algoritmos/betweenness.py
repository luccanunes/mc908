import networkx as nx

def read_graph():
    # Lê o número de vértices (n) e arestas (m)
    n, m = map(int, input().split())
    
    # Cria um grafo direcionado
    G = nx.MultiDiGraph()
    
    # Lê as arestas e adiciona ao grafo
    for _ in range(m):
        a, b = input().split()
        G.add_edge(a, b)
    
    return G

def main():
    # Lê o grafo
    G = read_graph()
    
    # Calcula a betweenness centrality
    betweenness = nx.betweenness_centrality(G)
    
    # Ordena os vértices pelo valor de betweenness centrality
    sorted_vertices = sorted(betweenness.items(), key=lambda item: item[1], reverse=True)
    
    # Imprime os vértices ordenados
    for vertex, centrality in sorted_vertices:
        print(f'{vertex}')

if __name__ == "__main__":
    main()