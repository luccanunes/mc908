import requests
import json

# Carrega o arquivo users.json
with open('users.json', 'r') as file:
    users = json.load(file)

# URL base para a requisição de feed
base_url = "https://public.api.bsky.app/xrpc/app.bsky.feed.getAuthorFeed"
limit = 100
filter_type = "posts_no_replies"

# Headers para a requisição
headers = {
    'Accept': 'application/json'
}

# Dicionário para armazenar os posts de cada usuário
user_feeds = {}

# Função para extrair os campos especificados de um post
def extract_post_fields(post):
    return {
        'uri': post.get('uri'),
        'cid': post.get('cid'),
        'author_handle': post.get('author', {}).get('handle'),
        'replyCount': post.get('replyCount'),
        'repostCount': post.get('repostCount'),
        'likeCount': post.get('likeCount'),
        'quoteCount': post.get('quoteCount')
    }

# Faz a requisição de feed para cada usuário
for user in users[:100]:
    params = {
        'actor': user,
        'limit': limit,
        'filter': filter_type
    }
    
    response = requests.get(base_url, headers=headers, params=params)
    
    if response.status_code != 200:
        print(f"Error fetching feed for {user}: {response.status_code}")
        continue

    data = response.json()
    feed = data.get('feed', [])
    
    # Extrai os campos especificados de cada post
    user_posts = [extract_post_fields(item['post']) for item in feed if 'post' in item]
    
    # Armazena os posts no dicionário
    user_feeds[user] = user_posts

# Converte o dicionário para uma string JSON
json_output = json.dumps(user_feeds, indent=4)
# print(json_output)

# Opcional: Salva o resultado em um arquivo JSON
with open('user_feeds.json', 'w') as outfile:
    json.dump(user_feeds, outfile, indent=4)