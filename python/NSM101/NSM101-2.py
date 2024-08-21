import time

U = open("uaiai (1).txt","r").readlines()

UT = [int(i[0:10]) for i in U]

UA = [i[11:43] for i in U]

UU = {}
UC = []

print(int(time.mktime(time.strptime("29.08.2021 19:27:03", "%d.%m.%Y %H:%M:%S"))))
print(int(time.mktime(time.strptime("29.10.2021 09:48:39", "%d.%m.%Y %H:%M:%S"))))
print()

for i in U:
    if int(time.mktime(time.strptime("29.08.2021 19:27:03", "%d.%m.%Y %H:%M:%S"))) <= int(i[0:10]) <= int(time.mktime(time.strptime("29.10.2021 09:48:39", "%d.%m.%Y %H:%M:%S"))):
        print(i[0:43])
        UC.append(i)
        if i[11:43] in UU: UU[i[11:43]] += 1
        else: UU[i[11:43]] = 1

print()
print(len(UC))       
print(len(UU))
print()


US = []

for i in UU:
    if UU[i] >= 2:
        print(i,":",UU[i])
        US.append(UU[i]-1)
        
print(sum(US))
        
# print(UA)