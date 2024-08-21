def findGenes(genome:str)->list[str]:
    i=[genome.upper(),0,0]
    while True:
        i[1]=i[0][i[2]:].find("ATG")+i[2]+3
        if(i[1]==2):break
        j=[-1,-1,-1]
        j[0]=i[0][i[1]:].find("TAG")
        j[1]=i[0][i[1]:].find("TAA")
        j[2]=i[0][i[1]:].find("TGA")
        try:i[2]=min([k for k in j if k>0])+i[1]
        except:break
        i.append(i[0][i[1]:i[2]])
    try:i[3]
    except IndexError:i.append("No genes found")
    return i[3:]