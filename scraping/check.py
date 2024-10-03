import json

# Carrega o arquivo users.json
with open('users.json', 'r') as file:
    all_handles = json.load(file)

# Verifica se há handles duplicados
unique_handles = set()
duplicates = set()

for handle in all_handles:
    if handle in unique_handles:
        duplicates.add(handle)
    else:
        unique_handles.add(handle)

if duplicates:
    print("Handles duplicados encontrados:")
    print(duplicates)
else:
    print("Nenhum handle duplicado encontrado.")