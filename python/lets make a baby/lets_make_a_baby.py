try:
    year = int(input("enter a year between 2001 and 2010: "))
    if not 2001 <= year <= 2010: raise ValueError
    gender = int(input("boy(0),girl(1): "))*2+1
    if not gender == 1 and not gender == 3: raise ValueError
    name = input("enter a name: ")

    with open("babynameranking"+str(year)+".txt","r") as file:
        for i in range(1000):
            string = file.readline().split("	")
            if name.lower() == string[gender].lower().strip(): 
                print("rank:",string[0],"|",string[gender+1])
                break
            if i == 999: print("name not found")
except: print("you did something wrong. idiot. dummy. dunce. i hope you feel bad")