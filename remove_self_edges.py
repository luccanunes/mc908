import networkx as nx

def remove_self_loops(gexf_input, gexf_output):
    # Carregar o grafo do arquivo GEXF
    G = nx.read_gexf(gexf_input)
    
    # Remover auto-laços
    G.remove_edges_from(nx.selfloop_edges(G))
    
    # Salvar o grafo modificado em um novo arquivo GEXF
    nx.write_gexf(G, gexf_output)
    print(f"Auto-laços removidos e grafo salvo em {gexf_output}")

# Exemplo de uso
gexf_input = 'rede_eleicoes_15000.gexf'  # Substitua pelo caminho do seu arquivo GEXF de entrada
gexf_output = 'rede.gexf'  # Substitua pelo caminho do seu arquivo GEXF de saída

remove_self_loops(gexf_input, gexf_output)