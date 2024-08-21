def errorHandler(number):
    try:
        number = int(number)
    except:
        print("invalid input! user error. please refer to user manual 3 page 5211 paragraph 13")
        return False
    if (number >= 0 and number <= 15):
        return True
    else:
        return False

def getInput():
    while True:
        number = input("Human, please enter a number between 0 and 15: ")
        if (errorHandler(number)):
            break
    return int(number)

number = getInput()
binNumber = bin(number)
binNumber = binNumber[2:]
print("the binary value for ", number, " is : ", binNumber)