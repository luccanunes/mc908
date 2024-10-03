import requests
import json

url = "https://public.api.bsky.app/xrpc/app.bsky.actor.searchActors"
query = "bsky.social"
limit = 100

headers = {
    'Accept': 'application/json',
}

all_handles = []
cursor = None

for _ in range(100):
    params = {
        'q': query,
        'limit': limit
    }
    if cursor:
        params['cursor'] = cursor

    response = requests.get(url, headers=headers, params=params)
    
    if response.status_code != 200:
        print(f"Error: {response.status_code}")
        break

    data = response.json()
    actors = data.get('actors', [])
    handles = [actor['handle'] for actor in actors]
    all_handles.extend(handles)

    cursor = data.get('cursor')
    if not cursor:
        break

# Converte a lista de handles para uma string JSON
json_output = json.dumps(all_handles, indent=4)
print(json_output)