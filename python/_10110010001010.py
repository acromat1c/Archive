try:
    userInput=int(input("enter a positive integer: "))
    if(userInput<0):raise
    theList=[1,str()]
    while True:
        if(sum(theList[0:-2])>=userInput):break
        theList.insert(0,theList[0]*2)
    for i in theList:
        if(userInput>=int(i)):
            userInput-=int(i)
            theList[-1]+="1"
        else:theList[-1]+="0"
    print("the binary value is: ",theList[-1])
except:print("user error")