import time




U = open("uaiai (1).txt","r").readlines()
UT = [int(UA[0:10]) for UA in U]
US = [UA[11:43] for UA in U]
UC = [J for i, J in enumerate(U) if U.index(J) == i]
print(len(US))
print(len(UC))
print(US[1])

s = 0
e = 0

UD = []

for ei, i in enumerate(UT):
    if time.mktime(time.strptime("29.08.2021 19:27:03", "%d.%m.%Y %H:%M:%S")) >= i <= time.mktime(time.strptime("29.10.2021 09:48:39", "%d.%m.%Y %H:%M:%S")):
        UD.append(i)
  
# for ei, i in enumerate(UT):
#     if i >= time.mktime(time.strptime("29.10.2021 09:48:39", "%d.%m.%Y %H:%M:%S")):
#         print(ei, "\n", i, sep="")
#         e = ei
#         break
    
print(len(UD))
#print(US)

# with open("uaiai.txt","r") as U: 
#     A = U.readlines() 
#     print(len([J for i, J in enumerate(A) if A.index(J) == i]))

count=0
UW = []
for item in UD:
    if item not in UW:
        count += 1
        UW.append(item)
print(len(UW))
print(count)

#print(len([J for i, J in enumerate(UD) if UD.index(J) == i]))

#print(len(U))
#print(len("1630258821|272e45fdae0ddda1d579a31da476b3c7"))