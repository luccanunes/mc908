import pandas as pd
import networkx as nx
import matplotlib.pyplot as plt
import imageio
import os

# Função para ler os resultados da simulação
def read_results(file_path):
    df = pd.read_csv(file_path)
    return df

# Função para simular a propagação da influência e criar o GIF
def create_influence_gif(G, df, steps, output_file, node_size=300, edge_width=1, frame_duration=1):
    frames = []

    # Criar a subpasta 'gif' se não existir
    if not os.path.exists('gif'):
        os.makedirs('gif')

    # Calcular a posição dos vértices uma vez usando o layout Kamada-Kawai
    pos = nx.kamada_kawai_layout(G)

    # Conjuntos para manter os nós infectados
    infected_by_alg1 = set()
    infected_by_alg2 = set()

    for step in range(steps + 1):
        # Atualizar os conjuntos de nós infectados
        infected_by_alg1.update(set(df[(df['step'] == step) & (df['algorithm'] == 'alg1')]['node']))
        infected_by_alg2.update(set(df[(df['step'] == step) & (df['algorithm'] == 'alg2')]['node']))

        print(f"step: {step}, inf1: {infected_by_alg1}, inf2: {infected_by_alg2}")
        color_map = []
        for node in G:
            if int(node) in infected_by_alg1:
                color_map.append('red')
            elif int(node) in infected_by_alg2:
                color_map.append('blue')
            else:
                color_map.append('gray')

        plt.figure(figsize=(10, 10))
        nx.draw(G, pos, node_color=color_map, with_labels=True, node_size=node_size, width=edge_width, font_size=12)
        plt.title(f'Step {step + 1}')
        frame_path = f'gif/frame_{step}.png'
        plt.savefig(frame_path)
        plt.close()

        frames.append(imageio.imread(frame_path))

    gif_path = os.path.join('gif', output_file)
    imageio.mimsave(gif_path, frames, duration=frame_duration)

# Carregar o grafo do arquivo .gexf
G = nx.read_gexf('rede.gexf')

# Ler os resultados da simulação
df = read_results('results.csv')

# Criar o GIF com tamanhos de vértices e arestas ajustados
create_influence_gif(G, df, steps=10, output_file='influence_simulation.gif', node_size=700, edge_width=3, frame_duration=700)

print("GIF salvo como 'gif/influence_simulation.gif'")