import json

# Carrega o arquivo users_feeds_full.json
with open('./../scraping/user_feeds_full.json', 'r') as file:
    all_feeds = json.load(file)

# Carrega o arquivo users.json
with open('./../scraping/users.json', 'r') as file:
    users = json.load(file)

users_set = set(users)

# Lista para feed e autor
feed_author_list = []
lista = set()

# Itera pelos feeds e posts
for feed_name, posts in all_feeds.items():
    for post in posts:
        author = post['author_handle']
        if(not (author in users_set)):
            lista.add(author)
        if(author != feed_name and author in users_set):
            # lista.add((feed_name, author))
            feed_author_list.append({'feed': feed_name, 'author': author})

# Exibe a lista resultante
for item in feed_author_list:
    print(f"{item['author']} {item['feed']}") # aresta author -> item[feed]

print()

for x in lista:
    print(x)

# Salva em um arquivo JSON
# with open('feed_author_list.json', 'w') as file:
#     json.dump(feed_author_list, file, indent=4)