try:
    i=[int(input("first 9 characters of IBSN: ")),1,0]
    if not(len(str(i[0]))==9):raise
    while i[1]<=9:
        i[2]+=i[1]*int(str(i[0])[i[1]-1])
        i[1]+=1
    i[2]%=11
    if(i[2]==10):i[2]='x'
    print(f"IBSN: {i[0]}{i[2]}")
except:print("user error")