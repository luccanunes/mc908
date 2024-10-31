import requests
import networkx as nx

# Inicialize o grafo
G = nx.DiGraph()

# Função para buscar posts contendo a string "Eleições"
def search_posts(query, cursor=None, limit=100):
    url = f"https://public.api.bsky.app/xrpc/app.bsky.feed.searchPosts?q={query}&limit={limit}"
    if cursor:
        url += f"&cursor={cursor}"
    response = requests.get(url)
    return response.json()

# Função para obter reposts de um post
def get_reposts(post_uri):
    url = f"https://public.api.bsky.app/xrpc/app.bsky.feed.getRepostedBy?uri={post_uri}"
    response = requests.get(url)
    return response.json()

# String de interesse
query = "Eleições"
cursor = None
total_vertices = 0

while total_vertices < 10:
    print("vertices: ", total_vertices)
    # Buscar posts contendo a string
    data = search_posts(query, cursor)
    print("data ", data)
    posts = data.get("posts", [])
    print("posts ", data)
    cursor = data.get("cursor", None)
    print("cursor ", data)

    for post in posts:
        post_uri = post['uri']
        author_handle = post['author']['handle']
        
        # Obter reposts do post
        repost_data = get_reposts(post_uri)
        reposts = repost_data.get("repostedBy", [])
        
        for repost in reposts:
            repost_handle = repost['handle']
            # Adicione a aresta ao grafo
            G.add_edge(author_handle, repost_handle)
        
        # Atualize o total de vértices
        total_vertices = len(G.nodes)
        if total_vertices >= 10000:
            break

    if not cursor:
        break  # Se não houver mais páginas, saia do loop

# Salvar o grafo para análise posterior
nx.write_gexf(G, "rede_eleicoes.gexf")

print(f"Total de vértices: {total_vertices}")
print("Grafo salvo como 'rede_eleicoes.gexf'")