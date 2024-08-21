theList = []
while True:
    userInput = input("Enter an item (blank to quit): ")
    if(userInput != ""):theList.append(userInput)
    else:
        print("The items are " ,end="")
        theList[-2]=theList[-2]+" and "+theList[-1]
        for itemIndex, item in enumerate(theList[0:-1]):
            if(len(theList)-2!=itemIndex):item+=", "
            print(item,end="")
        print()
        break