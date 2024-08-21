i=[input("input genome: ").upper(),0,0]
while True:
    i[1]=i[0][i[2]:].find("ATG")+i[2]
    if(i[1]==-1):break
    i[1]+=3
    j=[-1,-1,-1]
    j[0]=i[0][i[1]:].find("TAG")
    j[1]=i[0][i[1]:].find("TAA")
    j[2]=i[0][i[1]:].find("TGA")
    try:i[2]=min([k for k in j if k>0])+i[1]
    except:break
    print(i[0][i[1]:i[2]])