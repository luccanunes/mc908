import requests
import networkx as nx

# Inicialize o grafo
G = nx.DiGraph()

# Função para buscar posts contendo a string de interesse
def search_posts(query, cursor=None, limit=100):
    url = f"https://public.api.bsky.app/xrpc/app.bsky.feed.searchPosts?q={query}&limit={limit}"
    if cursor:
        url += f"&cursor={cursor}"
    response = requests.get(url)

    if response.status_code != 200:
        print(f"Erro na requisição com query {query} e cursor {cursor}: {response.status_code}")
        return None
    
    try:
        return response.json()
    except requests.exceptions.JSONDecodeError:
        print(f"Erro ao decodificar a resposta JSON com query {query} e cursor {cursor}")
        print("Conteúdo da resposta:", response.text)
        return None

# Função para obter reposts de um post
def get_reposts(post_uri):
    url = f"https://public.api.bsky.app/xrpc/app.bsky.feed.getRepostedBy?uri={post_uri}"
    response = requests.get(url)

    if response.status_code != 200:
        print(f"Erro na requisição: {response.status_code}")
        return None
    
    try:
        return response.json()
    except requests.exceptions.JSONDecodeError:
        print("Erro ao decodificar a resposta JSON")
        print("Conteúdo da resposta:", response.text)
        return None

processed_posts = set()

# Lista de palavras-chave de interesse
queries = ["Eleições", "eleicoes", 
            "Política", "politica",
            "Governo",
            "Corrupção", "corrupcao",
            "Democracia",
            "Votação", "votacao",
            "Candidato", 
            "Partido",
            "congresso",
            "senado",
            "deputado",
            "presidente",
            "prefeito",
            "governador"
            "vereador",
            "campanha",
            "debate",
            "reforma",
            "saude", "saúde",
            "educacao", "educação", 
            "esquerda", "direita",
            "comunista", "comunismo",
            "fascista", "fascismo",
            "justia", "justica",
            "impeachment",
            "protesto",
            "movimento",
            "greve",
            "manifestacao", "manifestação",
            ]

# Número alvo de vértices
target_vertices = 10000
total_vertices = 0

for query in queries:
    cursor = None
    while total_vertices < target_vertices:
        print("Vertices: ", total_vertices)
        # Buscar posts contendo a string
        data = search_posts(query, cursor)
        if data is None:
            break  # Se houver um erro na requisição, saia do loop e passe para a próxima palavra-chave
        posts = data.get("posts", [])
        cursor = data.get("cursor", None)

        for post in posts:
            post_uri = post['uri']
            author_handle = post['author']['handle']
            
            if post_uri in processed_posts:
                continue
            processed_posts.add(post_uri)

            # Obter reposts do post
            repost_data = get_reposts(post_uri)
            if repost_data is None:
                continue  # Se houver um erro na requisição, pule para o próximo post
            reposts = repost_data.get("repostedBy", [])
            
            for repost in reposts:
                repost_handle = repost['handle']
                # Adicione a aresta ao grafo
                G.add_edge(author_handle, repost_handle)
            
            # Atualize o total de vértices
            total_vertices = len(G.nodes)
            if total_vertices >= target_vertices:
                break

        if not cursor:
            break  # Se não houver mais páginas, saia do loop

    if total_vertices >= target_vertices:
        break  # Se atingiu o número desejado de vértices, saia do loop principal

# Salvar o grafo para análise posterior
nx.write_gexf(G, "rede_eleicoes.gexf")

print(f"Total de vértices: {total_vertices}")
print("Grafo salvo como 'rede_eleicoes.gexf'")