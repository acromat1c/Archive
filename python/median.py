from statistics import median, mean

frekvenstabell = [(2,0), (0,1), (5,2), (1,3), (4,4), (5,5), (7,6), (3,7)]

list = []

for (x,f) in frekvenstabell:
    list += f*[x]

print("medianen er", median(list))
print("gjennomsnittet er", round(mean(list), 2))