try:
    timeTotal = str()
    userInput = int(input("enter time in seconds: "))
    time = [str(int(userInput / 3600))]
    time.append(str(int((userInput - int(time[0]) * 3600) / 60)))
    time.append(str(userInput - int(time[0]) * 3600 - int(time[1]) * 60))
    for i in time:
        if (str(i) == 0): i = str(00)
        elif (len(str(i)) == 1): i = str(0) + i
        timeTotal += str(i) + ":"
    print(timeTotal[0:-1])
except: print("user error")