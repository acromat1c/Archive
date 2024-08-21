def isItAnInteger(theNumber):
    try:
        int(theNumber)
        return True
    except ValueError:
        return False

while True:
    while True:
        userInput = input("Give me a number (int)! i dear you!: ")
        if (isItAnInteger(userInput)):
            break
    reverseAnswer = str(userInput)[::-1]
    print()
    print(userInput)
    print(reverseAnswer)
    if (userInput == reverseAnswer):
        print("true")
    else:
        print("false")
    print("\n","again?")
    yN = input("y/n: ")
    if (yN == 'n'):
        break