from random import randint

# Entradas
min_sedes = 8
max_sedes = 50
min_custo = 1
max_custo = 1000
min_demanda = 1
max_demanda = 100

# Quantidade de vertices e arestas
vertices = randint(min_sedes, max_sedes)
arestas = randint((vertices*8)/2, (vertices*(vertices-1)) / 2)

print(vertices, arestas)

# Inicio, fim e demanda
inicio = randint(1, vertices)
fim = randint(1, vertices)
while (inicio == fim):
    fim = randint(1, vertices)

if (inicio > fim):
    inicio, fim = fim, inicio

demanda = randint(min_demanda, max_demanda)
print(inicio, fim, demanda)

# Matriz com os pesos das arestas
matriz = [[0 for i in range(arestas)] for i in range(arestas)]

while (arestas != 0):
    a = randint(1, vertices)
    b = randint(1, vertices)
    custo = randint(min_custo, max_custo)
    if (abs(a-b) > 2):
        continue

    if (a != b and matriz[a][b] == 0 and matriz[b][a] == 0):
        matriz[a][b] = custo
        matriz[b][a] = custo
        print(a, b, custo)

        arestas -= 1
        



