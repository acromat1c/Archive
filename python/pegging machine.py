from random import randrange
try:
    userInput=input("[balls, peg-layers, path(y/n)]: ").lower().replace(" ","")
    inputDiv=userInput.find(",")
    if(inputDiv!=userInput.rfind(",")):inputDivR=userInput.rfind(",")
    else:inputDivR=len(userInput)
    layers=int(userInput[inputDiv+1:inputDivR])
    if(inputDiv==-1 or layers<=0 or int(userInput[:inputDiv])<=0):raise
    result=list(range(layers*2+2))
    for i in result:result[i]=0
    path=False
    if (userInput[-1]=='y'):path=True
    for i in list(range(int(userInput[:inputDiv]))):
        if(path==True):
            print()
            for c in range(layers*3+len(str(i))-1):print("-",end="")
            print()
            print(i+1,end=": ")
        i=0
        for j in range(layers+1):
            j=randrange(0,2)
            if(j==0):j=-1
            i+=j
            if(path==True):
                if(j==1):j="+"+str(j)
                print(str(j)[0],end="|")
        result[i+layers]+=1
    print("\n")
    for c, i in enumerate(result[1::2]):print(result[1::2][c],"|",end="")
except:print("user error")

#imput format: (number of balls), (peg layers), (path)
#write everything on one line seperating the values with a ",".
#note: the last variable (path) and is optional