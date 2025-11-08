from gurobipy import *
import numpy as np

def callback(model, where):
    if where == GRB.Callback.MIPNODE:
        node_count = model.cbGet(GRB.Callback.MIPNODE_NODCNT)
        if node_count == 0:
            obj_value = model.cbGet(GRB.Callback.MIPNODE_OBJBND)
            print(f"Valor de la relajación lineal del modelo compacto: {obj_value}")
            model.terminate()

def compacta(m, L, l, d):
    n = int(sum(d))
    model = Model()
    x = model.addVars(n, vtype=GRB.BINARY)
    y = model.addVars(m, n, vtype=GRB.INTEGER)
    z = model.addVars(m, n, vtype=GRB.BINARY)
    f = model.addVars(n)

    model.setObjective(sum(L*x[j] + f[j] for j in range(n)), GRB.MINIMIZE)

    model.addConstrs(sum(y[i, j] for j in range(n)) == d[i] for i in range(m))
    model.addConstrs(sum(l[i]*y[i, j] for i in range(m)) <= L*x[j] for j in range(n))
    model.addConstrs(y[i, j] <= L*z[i, j] for i in range(m) for j in range(n))
    model.addConstrs(f[j] >= abs(l[i] - l[k]) * (z[i, j] + z[k, j] - 1) for j in range(n) for i in range(m) for k in range(m))

    model.optimize(callback)

    print(f"Valor del modelo compacto: {model.ObjVal}")

def getcolumn(m, L, l, pi):
    
    model = Model()
    
    lmin = model.addVar()
    lmax = model.addVar()
    a = model.addVars(m, vtype=GRB.INTEGER)
    z = model.addVars(m, vtype=GRB.BINARY)
    
    model.addConstr(sum(l[i]*a[i] for i in range(m)) <= L)
    model.addConstrs(a[i] <= L*z[i] for i in range(m))
    model.addConstrs(lmin <= l[i]*z[i] + L*(1 - z[i]) for i in range(m))
    model.addConstrs(lmax >= l[i]*z[i] for i in range(m))
    
    model.setObjective(L + lmax - lmin - sum(pi[i]*a[i] for i in range(m)), GRB.MINIMIZE)
    
    model.optimize()
    
    if model.ObjVal >= 0.0:
        return None, None

    columna = []
    for i in range(m):
        columna.append(a[i].X)
    
    return columna, L + lmax.X - lmin.X

def gencolumnas(m, L, l, d):
    
    model = Model()
    
    x = []
    R = []
    
    for _ in range(m):
        x.append(model.addVar())
    
    for i in range(m):
        R.append(model.addConstr(x[i] == d[i]))
    
    model.setObjective(sum(L*x[i] for i in range(m)), GRB.MINIMIZE)
    
    while True:
        model.optimize()
        pi = [r.Pi for r in R]
        columna, v = getcolumn(m, L, l, pi)
        if columna == None:
            break
        col = Column()
        for i in range(m):
            col.addTerms(columna[i], R[i])
        x.append(model.addVar(obj = v, column = col))
        
    print(f"La generación de columnas relajada dio {model.ObjVal}")
    
    for i in range(len(x)):
        x[i].setAttr(GRB.Attr.VType, GRB.INTEGER)
        
    model.optimize()
    
    print(f"La generación de columnas dio {model.ObjVal}")

setParam('OutputFlag', 0)

np.random.seed(1)
m = 5
L = 40
l = np.random.randint(5, 20, m)
d = np.random.randint(5, 20, m)

compacta(m, L, l, d)
gencolumnas(m, L, l, d)