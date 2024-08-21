import os.path
import pickle
from Hacking_To_The_Gate import *
from breaking_the_law import *

NEW_CAR_CHOICE = 1
NEW_TRUCK_CHOICE = 2
NEW_SUV_CHOICE = 3
FIND_VEHICLE_CHOICE = 4
SHOW_VEHICLES_CHOICE = 5
CHECK_FOR_TICKETS = 6
SHOW_TICKETS = 7
SAVE_CHOICE = 8
QUIT_CHOICE = 9

filePath = "vehiclesList.pickle"

def create(vehicleType):
    try:
        j = [input("Registry Number: "),input("Model: "),int(input("Make: ")),int(input("Milage: ")),int(input("Price: "))]
        if not(len(j[0]) == 7 and j[2] >= 0 and j[3] >= 0 and j[4] >= 0): raise TypeError
        if vehicleType == "Car":
            i = int(input("Doors: "))
            if i >= 0:
                j.append(i)
                return "success",Vehicle.Car(*j)
            else: raise TypeError
        elif vehicleType == "SUV":
            i = int(input("Pass_cap : "))
            if i >= 0:
                j.append(i)
                return "success",Vehicle.SUV(*j)
            else: raise TypeError
        elif vehicleType == "Truck":
            i = input("Drive_type: ")
            if i == "2WD" or i == "4WD":
                j.append(i)
                return "success: ",Vehicle.Truck(*j)
            else: raise TypeError
        else: raise TypeError
    except: return("something went wrong")

def CheeseWheel():   
    if os.path.isfile(filePath):
        with open(filePath, "rb") as file:
            return pickle.load(file)
    else: return []
        
def MilkWheel(vehicles_list):
    with open(filePath, "wb") as file:
        pickle.dump(vehicles_list, file)

def WheelOfFortune(vehicles_list, model):
    allTheCars = []
    for i in vehicles_list:
        if model.lower() in i.model.lower(): allTheCars.append(i)
    return allTheCars
    
def WheelOfAgony(vehicles_list):
    input0 = input("file for camera box 1:")
    input1 = input("file for camera box 2:")
    input2 = input("speed limit:")
    input3 = input("distance:")
    try:
        input2 = int(input2)
        input3 = int(input3)
        speeders = checkForSpeeding(input0,input1,input2,input3)
        for entitie in speeders:
            for vehicle in vehicles_list:
                if entitie in vehicle.registryNumber:
                    vehicle.registerTicket(speeders[entitie][0],speeders[entitie][1],input2)
                    print("ticket found for", entitie)
    except: print("something went wrong")

def main():
    vehicles_list = CheeseWheel()
    choice = 0
    while choice != QUIT_CHOICE:
        display_menu()
        try: choice = int(input('Enter your choice: '))
        except: choice = 0
        def createSomething(v):
            if len(v) == 2:
                print(*v)
                vehicles_list.append(v[1])
            else: print(v)
        if choice == NEW_CAR_CHOICE:
            createSomething(create("Car"))   
        elif choice == NEW_TRUCK_CHOICE:
            createSomething(create("Truck"))
        elif choice == NEW_SUV_CHOICE:
            createSomething(create("SUV"))
        elif choice == FIND_VEHICLE_CHOICE:
            print("\n".join(map(lambda s: str(s),WheelOfFortune(vehicles_list, input("Name of vehicle: ")))))
        elif choice == SHOW_VEHICLES_CHOICE:
            print('The following cars are in inventory:')
            for item in vehicles_list:
                print(item)
        elif choice == CHECK_FOR_TICKETS:
            WheelOfAgony(vehicles_list)
        elif choice == SHOW_TICKETS:
            for vehicle in vehicles_list: 
                if len(vehicle.tickets()) != 0: 
                    print(*vehicle.tickets(),sep="\n")
        elif choice == SAVE_CHOICE:
            MilkWheel(vehicles_list)
            print('Save complete!')
            exit()
        elif choice == QUIT_CHOICE:
            print('Exiting the program...')
            exit()
        else:
            print('Error: invalid selection.')

def display_menu():
    print(' MENU')
    print('1) New car')
    print('2) New truck')
    print('3) New SUV')
    print('4) Find vehicles by make')
    print('5) Show all vehicles')
    print('6) Check for tickets')
    print('7) show tickets')
    print('8) Save')
    print('9) Quit')

if __name__ == '__main__':
    main()