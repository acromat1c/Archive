U = open("uaiai (1).txt","r").readlines()

UD = {}
for i in U:
    j = i[10:44]
    if j in UD:
        UD[j] += 1
    else:
        UD[j] = 1

UD = {k: v for k, v in sorted(UD.items(), key=lambda item: item[1])}

print(UD)