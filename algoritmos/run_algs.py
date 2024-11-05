python
import os
import subprocess
import argparse

# Configurar o analisador de argumentos
parser = argparse.ArgumentParser(description='Executar programas de algoritmos passando um arquivo específico como entrada padrão.')
parser.add_argument('input_file', type=str, help='O arquivo de entrada para os programas de algoritmos')
parser.add_argument('algorithms_dir', type=str, help='O diretório contendo os programas de algoritmos')

# Analisar os argumentos
args = parser.parse_args()

# Listar os programas na pasta `algoritmos`
algorithms = [
    "betweeness", "closeness", "eigenvector", "maxdegree", 
    "maxdegreenorep", "pageranking", "pagerankingrev"
]

# Caminho completo para o diretório de algoritmos
algorithms_dir = args.algorithms_dir

# Executar cada programa
for algorithm in algorithms:
    program_path = os.path.join(algorithms_dir, f"{algorithm}.cpp")
    executable = f"{algorithm}.exe"
    output_file = f"{algorithm}_list.txt"
    
    # Compilar o programa (assumindo que você está usando g++)
    compile_command = ["g++", "-o", executable, program_path]
    subprocess.run(compile_command, check=True)
    
    # Executar o programa passando o arquivo de entrada como entrada padrão
    with open(args.input_file, 'r') as input_file, open(output_file, 'w') as output_file:
        subprocess.run([f"./{executable}"], stdin=input_file, stdout=output_file, check=True)

print("Todos os programas foram executados com sucesso.")