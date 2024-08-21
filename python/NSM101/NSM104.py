T = [i.split('",') for i in open("error-on-lines.csv","r").readlines()[1:]]
for ei, i in enumerate(T):
    T[ei][-1] = T[ei][-1].rstrip("\n")
    for ej, j in enumerate(i[0:-1]):
        T[ei][ej] = T[ei][ej]+'"'
print(*T,sep="\n")

methods = ["GET","PUT","POST","DELETE","PATCH","HEAD","OPTIONS","TRACE","CONNECT"]

E = {}
for ei, i in enumerate(T):
    if len(i) != 4: 
        E[ei+2] = i
        continue
    elif i[3] not in methods:
        E[ei+2] = i
        continue
    
print(E,sep="\n")

# 4334:757