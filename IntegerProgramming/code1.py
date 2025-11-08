from gurobipy import Model, GRB, setParam
import numpy as np

N = 10
EPS = 1e-2
K = 6

def getcut(V, E, xhat, epsilon = EPS, k = K):
    
    sat = Model()
    
    f = sat.addVars(E, ub = 1 - epsilon)
    g = sat.addVar(ub = 1 - epsilon)
    alpha = sat.addVars(E, lb = -float('inf'), vtype = GRB.INTEGER)
    beta = sat.addVar(lb = -k, ub = k, vtype = GRB.INTEGER)
    mu = sat.addVars(V)
    
    sat.addConstrs(mu[i] + mu[j] == alpha[i,j] + f[i,j] for (i,j) in E)
    sat.addConstr(sum(mu[v] for v in V) <= beta + g)
    
    sat.setObjective(sum(xhat[i,j].X*alpha[i,j] for (i,j) in E) - beta, GRB.MAXIMIZE)
    
    sat.optimize()
    
    cut = {(i, j): alpha[i, j].X for (i, j) in E}  
    
    return sat.ObjVal, cut, beta.X

setParam('OutputFlag', 0)
np.random.seed(1)

iters = 0
n = N
error = 1e-4

V = range(n)
w = dict()

for i in V:
    for j in V:
        if i < j:
            w[i, j] = np.random.randint(10, 20)

print(w)

E = w.keys()

lp = Model()

x = lp.addVars(E)

lp.addConstrs(sum(x[i,j]for j in V if (i,j) in E) + sum(x[j,i] for j in V if (j,i) in E) <= 1 for i in V)
lp.setObjective(sum(w[i,j]*x[i,j] for (i,j) in E), GRB.MAXIMIZE)

lastvalue = 0

while True:
    lp.optimize()
    if abs(lp.ObjVal - lastvalue) < error:
        break
    vcut, cut, bcut = getcut(V, E, x)
    if vcut <= 0:
        break
    lp.addConstr(sum(cut[i, j]*x[i, j] for (i, j) in E) <= bcut)
    iters += 1

fracciones = 0

for i, j in E:
    if x[i,j].X > 0.01 and x[i, j].X < 0.99:
        fracciones += 1
        
milp = Model()

xb = milp.addVars(E, vtype = GRB.BINARY)

milp.addConstrs(sum(xb[i,j]for j in V if (i,j) in E) + sum(xb[j,i] for j in V if (j,i) in E) <= 1 for i in V)
milp.setObjective(sum(w[i,j]*xb[i,j] for (i,j) in E), GRB.MAXIMIZE)

milp.optimize()

print(f"El modelo convergió luego de {iters} cortes y se solucionó con { fracciones } variables fraccionales")
print("Problema entero alcanzó óptimo:", milp.ObjVal)
print("Problema con cortes alcanzó óptimo:", lp.ObjVal)
