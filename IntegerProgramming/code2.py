from gurobipy import *
import numpy as np

#Bloque 1
def CB(model, where):
        
    if where == GRB.Callback.MIPNODE and model.cbGet(GRB.Callback.MIPNODE_NODCNT) == 0 and model.cbGet(GRB.Callback.MIPNODE_STATUS) == GRB.OPTIMAL:
    #if where == GRB.Callback.MIPNODE and model.cbGet(GRB.Callback.MIPNODE_STATUS) == GRB.OPTIMAL:

        for i in S:
            ysol = [0 for j in T]

            for j in T:
                ysol[j] = model.cbGetNodeRel(y[i,j])

            cutGeni[i].setObjective(sum(-ysol[j]*w1i[i][j] for j in T) + 2*sum(-ysol[j]*w2i[i][j] for j in T) + 2, GRB.MAXIMIZE)
            cutGeni[i].optimize()
            
            if cutGeni[i].status == GRB.OPTIMAL and cutGeni[i].ObjVal > 0.001:
                model.cbCut(sum(-y[i,j]*w1i[i][j].x for j in T) + 2*sum(-y[i,j]*w2i[i][j].x for j in T) + 2 <= 0) 
                cortes_i[0] += 1
                print("User cut")
            
        for j in T:
            ysol = [0 for i in S]

            for i in S:
                ysol[i] = model.cbGetNodeRel(y[i,j])

            cutGenj[j].setObjective(sum(-ysol[i]*w1j[j][i] for i in S) + 2*sum(-ysol[i]*w2j[j][i] for i in S) + 2, GRB.MAXIMIZE)
            cutGenj[j].optimize()
            
            if cutGenj[j].status == GRB.OPTIMAL and cutGenj[j].ObjVal > 0.001:
                model.cbCut(sum(-y[i,j]*w1j[j][i].x for i in S) + 2*sum(-y[i,j]*w2j[j][i].x for i in S) + 2 <= 0) 
                cortes_j[0] += 1
                print("User cut")

#Bloque 2
np.random.seed(2)

s = 30
t = 30
S = range(s)
T = range(t)

alpha = np.random.randint(1, 40, s)
beta = np.random.randint(1, 40, t)

delta = sum(alpha) - sum(beta)

if delta > 0:
    for j in range(delta):
        beta[j%t] += 1

if delta < 0:
    for i in range(-delta):
        alpha[i%s] += 1

print(alpha)
print(beta)

m = {(i,j): min(alpha[i],beta[j]) for i in S for j in T}

print(sum(alpha), sum(beta))

c = np.random.randint(200,800, (s,t))
f = np.random.randint(200,800, (s,t))

#Bloque 3
cutGeni = {}
w1i = {}
w2i = {}

for i in S:
    cutGeni[i] = Model()
    cutGeni[i].Params.OutputFlag = 0

    w1i[i] = cutGeni[i].addVars(T, vtype = GRB.BINARY)
    w2i[i] = cutGeni[i].addVars(T, vtype = GRB.BINARY)

    cutGeni[i].addConstr(sum(m[i,j]*(w1i[i][j]+w2i[i][j]) for j in T) >= (sum(m[i,j] for j in T) - alpha[i]) + 1)
    cutGeni[i].addConstrs(m[i,k]*w1i[i][k] <= sum(m[i,j]*(w1i[i][j]+w2i[i][j]) for j in T) - (sum(m[i,j] for j in T) - alpha[i]) - 1 for k in T)
    cutGeni[i].addConstrs(m[i,k]*w2i[i][k] >= sum(m[i,j]*(w1i[i][j]+w2i[i][j]) for j in T) - (sum(m[i,j] for j in T) - alpha[i]) - alpha[i]*(1-w2i[i][k]) for k in T)
    cutGeni[i].addConstrs(w1i[i][j] + w2i[i][j] <= 1 for j in T)
    
cutGenj = {}
w1j = {}
w2j = {}

for j in T:
    cutGenj[j] = Model()
    cutGenj[j].Params.OutputFlag = 0

    w1j[j] = cutGenj[j].addVars(S, vtype = GRB.BINARY)
    w2j[j] = cutGenj[j].addVars(S, vtype = GRB.BINARY)

    cutGenj[j].addConstr(sum(m[i,j]*(w1j[j][i]+w2j[j][i]) for i in S) >= (sum(m[i,j] for i in S) - beta[j]) + 1)
    cutGenj[j].addConstrs(m[k,j]*w1j[j][k] <= sum(m[i,j]*(w1j[j][i]+w2j[j][i]) for i in S) - (sum(m[i,j] for i in S) - beta[j]) - 1 for k in S)
    cutGenj[j].addConstrs(m[k,j]*w2j[j][k] >= sum(m[i,j]*(w1j[j][i]+w2j[j][i]) for i in S) - (sum(m[i,j] for i in S) - beta[j]) - beta[j]*(1-w2j[j][k]) for k in S)
    cutGenj[j].addConstrs(w1j[j][i] + w2j[j][i] <= 1 for i in S)

cortes_i = {}
cortes_j = {}
cortes_i[0] = 0
cortes_j[0] = 0

#Bloque 4
ip = Model()
ip.Params.PreCrush = 1

x = ip.addVars(S,T)
y = ip.addVars(S,T, vtype=GRB.BINARY)

ip.addConstrs(sum(x[i,j] for j in T) == alpha[i] for i in S)
ip.addConstrs(sum(x[i,j] for i in S) == beta[j] for j in T)
ip.addConstrs(x[i,j] <= m[i,j]*y[i,j] for i in S for j in T)

ip.setObjective(sum(c[i,j]*x[i,j] + f[i,j]*y[i,j] for i in S for j in T))

ip.optimize(CB)

print(f"Se hicieron {cortes_i[0]} cortes del tipo i")
print(f"Se hicieron {cortes_j[0]} cortes del tipo j")