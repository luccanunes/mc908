import pandas as pd
import networkx as nx
import matplotlib.pyplot as plt
import imageio
import os
import argparse
from PIL import Image
# Função para ler os resultados da simulação
def read_results(file_path):
    df = pd.read_csv(file_path)
    return df
# Função para redimensionar imagens para um tamanho fixo
def resize_image(image_path, size):
    with Image.open(image_path) as img:
        img = img.resize(size, Image.LANCZOS)
        img.save(image_path)
# Função para simular a propagação da influência e criar o GIF
def create_influence_gif(G, df, steps, output_file, frame_duration=1, alg1_name="Algorithm 1", alg2_name=None):
    frames = []
    # Criar a subpasta 'gif' se não existir
    if not os.path.exists('gif'):
        os.makedirs('gif')
    # Calcular a posição dos vértices uma vez usando o layout Kamada-Kawai
    pos = nx.kamada_kawai_layout(G)
    # Ajustar automaticamente o tamanho dos nós e a largura das arestas
    num_nodes = len(G.nodes)
    node_size = max(10000 / num_nodes, 10)  # Valor mínimo para node_size
    edge_width = 0.1
    # Conjuntos para manter os nós infectados
    infected_by_alg1 = set()
    infected_by_alg2 = set()
    for step in range(steps + 1):
        # Atualizar os conjuntos de nós infectados
        infected_by_alg1.update(set(df[(df['step'] == step) & (df['algorithm'] == 'alg1')]['node']))
        if alg2_name:
            infected_by_alg2.update(set(df[(df['step'] == step) & (df['algorithm'] == 'alg2')]['node']))
        color_map = []
        for node in G:
            if int(node) in infected_by_alg1:
                color_map.append('red')
            elif alg2_name and int(node) in infected_by_alg2:
                color_map.append('blue')
            else:
                color_map.append('gray')
        plt.figure(figsize=(10, 10))
        nx.draw(G, pos, node_color=color_map, with_labels=False, node_size=node_size, width=edge_width)
        plt.title(f'Passo {step}')
        # Adicionar a legenda
        red_patch = plt.Line2D([0], [0], marker='o', color='w', markerfacecolor='red', markersize=10, label=alg1_name)
        if alg2_name:
            blue_patch = plt.Line2D([0], [0], marker='o', color='w', markerfacecolor='blue', markersize=10, label=alg2_name)
            plt.legend(handles=[red_patch, blue_patch], loc='upper right')
        else:
            plt.legend(handles=[red_patch], loc='upper right')
        frame_path = f'gif/frame_{step}.png'
        plt.savefig(frame_path, bbox_inches='tight', pad_inches=0)
        plt.close()
        # Redimensionar a imagem para um tamanho fixo
        resize_image(frame_path, (800, 800))
        frames.append(imageio.imread(frame_path))
    # Calcular o vencedor e a quantidade de vértices infectados
    num_infected_alg1 = len(infected_by_alg1)
    num_infected_alg2 = len(infected_by_alg2) if alg2_name else 0
    if alg2_name:
        if num_infected_alg1 > num_infected_alg2:
            winner = alg1_name
        elif num_infected_alg2 > num_infected_alg1:
            winner = alg2_name
        else:
            winner = "Empate"
    # Adicionar um frame final com o vencedor e a quantidade de vértices infectados, mantendo o grafo na tela
    plt.figure(figsize=(10, 10))
    nx.draw(G, pos, node_color=color_map, with_labels=False, node_size=node_size, width=edge_width)
    plt.title('Resultado Final')
    if alg2_name:
        plt.text(0.5, 0.1, f'Vencedor: {winner}', horizontalalignment='center', verticalalignment='center', fontsize=20, transform=plt.gca().transAxes)
        plt.text(0.5, 0.05, f'{alg1_name}: {num_infected_alg1} vértices infectados', horizontalalignment='center', verticalalignment='center', fontsize=15, color='red', transform=plt.gca().transAxes)
        plt.text(0.5, 0.0, f'{alg2_name}: {num_infected_alg2} vértices infectados', horizontalalignment='center', verticalalignment='center', fontsize=15, color='blue', transform=plt.gca().transAxes)
    else:
        plt.text(0.5, 0.05, f'{alg1_name}: {num_infected_alg1} vértices infectados', horizontalalignment='center', verticalalignment='center', fontsize=15, color='red', transform=plt.gca().transAxes)
    frame_path = 'gif/frame_final.png'
    plt.savefig(frame_path, bbox_inches='tight', pad_inches=0)
    plt.close()
    # Redimensionar a imagem final para um tamanho fixo
    resize_image(frame_path, (800, 800))
    frames.append(imageio.imread(frame_path))
    gif_path = os.path.join('gif', output_file)
    imageio.mimsave(gif_path, frames, duration=frame_duration)
# Configurar o analisador de argumentos
parser = argparse.ArgumentParser(description='Simular a propagação da influência e criar um GIF.')
parser.add_argument('gexf_file', type=str, help='O caminho para o arquivo .gexf')
parser.add_argument('results_file', type=str, help='O caminho para o arquivo de resultados CSV')
parser.add_argument('alg1_name', type=str, help='O nome do algoritmo 1 (vermelho)')
parser.add_argument('--alg2_name', type=str, help='O nome do algoritmo 2 (azul)', default=None)
# Analisar os argumentos
args = parser.parse_args()
# Carregar o grafo do arquivo .gexf
G = nx.read_gexf(args.gexf_file)
# Ler os resultados da simulação
df = read_results(args.results_file)
# Nome fixo para o arquivo GIF de saída
output_file = 'influence_simulation.gif'
# Criar o GIF com tamanhos de vértices e arestas ajustados
create_influence_gif(G, df, steps=20, output_file=output_file, frame_duration=700, alg1_name=args.alg1_name, alg2_name=args.alg2_name)
print(f"GIF salvo como 'gif/{output_file}'")