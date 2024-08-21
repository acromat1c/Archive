T = [i.split(";") for i in open("theflow.csv","r").readlines()[1:]]
#print(T)
U = []

for i in T:
    #if i[1].split(":")[0] not in U:
        U.append(i[1].split(":")[0])
    #if i[2].split(":")[0] not in U:
        U.append(i[2].split(":")[0])

count=0
UW = []
for item in U:
    if item not in UW:
        count += 1
        UW.append(item)
print(len(UW))
print(count)
    
print(len(U))

#svar-oppgave 103 54