import json

test_file = 'A/easy_0.txt'
output_file = 'output.txt'
json_file = 'A/costos.json'

degree = {}
V = 0

with open(test_file, 'r') as f:
    line = f.readline()
    V = int(line)
    for i in range(V):
        line = f.readline()
        col, row = map(int, line.split())
        degree[(col, row)] = 0

costo = 0
valor = 0
is_valid = True

with open(output_file, 'r') as f:
    line = f.readline()
    valor = int(line)
    for i in range(V-1):
        line = f.readline()
        col1, row1, col2, row2 = map(int, line.split())
        if (col1, row1) in degree == False:
            is_valid = False
        if (col2, row2) in degree == False:
            is_valid = False
        costo = costo + abs(col1 - col2) + abs(row1 - row2)
        degree[(col1, row1)] = degree[(col1, row1)] + 1
        degree[(col2, row2)] = degree[(col2, row2)] + 1

print(costo, valor)
if costo != valor:
    is_valid = False

tests = ["easy_0", "easy_1", "easy_2",
            "medium_0", "medium_1", "medium_2",
            "hard_0", "hard_1", "hard_2"]

for test in tests:
    if test in test_file:
        key = test
        break

with open(json_file, "r") as file:
    comparador = json.load(file)

if comparador[key]["costo"] != costo:
    is_valid = False

objetivo = 0
for nodo in degree:
    objetivo = objetivo + 1
    if degree[nodo] > 6:
        objetivo = 1000000000000000000
    if degree[nodo] == 6:
        objetivo = objetivo + 6
    if degree[nodo] == 5:
        objetivo = objetivo + 2
    if degree[nodo] == 4:
        objetivo = objetivo + 1

if is_valid == False:
    print("INCORRECT: 0.00")
elif (objetivo/comparador[key]["obj"]) > 1.35:
    print("PARTIAL CORRECT: 0.59")
elif (objetivo/comparador[key]["obj"]) > 1.20:
    print("PARTIAL CORRECT: 0.75")
elif (objetivo/comparador[key]["obj"]) > 1:
    print("PARTIAL CORRECT: 0.84")
else:
    print("PARTIAL CORRECT: 1.00")
    