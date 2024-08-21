with open(input("file 1 path:"),"r+") as file:
    file1 = file.read()
with open(input("file 1 path:"),"r+") as file:
    file2 = file.read()

print("Viser antallet unike ord i begge filer (lengde av union() (operator |) de to mengdene)","\n",len(set(file1.split(" ")).union(set(file2.split(" ")))),"\n")    
print("Viser alle unike ord i begge filer (union()  (operator |) av de to mengdene)","\n",set(file1.split(" ")).union(set(file2.split(" "))),"\n")
print("Viser alle unike ord som forekommer bade i forste og andre fil (intersection() (operator & av de to mengdene)","\n",set(file1.split(" ")).intersection(set(file2.split(" "))),"\n")
print("Viser alle unike ord som forekommer i forste fil, men ikke i andre (difference() (operator -))","\n",set(file1.split(" ")).difference(set(file2.split(" "))),"\n")
print("Viser alle unike ord som forekommer i andre fil, men ikke i forste (difference() (operator -))","\n",set(file2.split(" ")).difference(set(file1.split(" "))),"\n")
print("Viser alle unike ord som forekommer enten i forste eller i andre fil, bortsett fra felles ord (symmetrisk differanse (operator ^)) (siste omskrevet: alle ord som forekommer enten i forste eller andre, men ikke i begge)","\n",set(file1.split(" ")).difference(set(file2.split(" "))).union(set(file2.split(" ")).difference(set(file1.split(" ")))),"\n")