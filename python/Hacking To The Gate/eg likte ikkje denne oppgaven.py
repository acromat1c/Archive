class Vehicle():
    class _common():
        @property    
        def make(self) -> int:
            return self._make
        @make.setter    
        def make(self, make: int) -> None:
            if isinstance(make,int):
                if make >= 0: self._make = make
        
        @property    
        def mileage(self) -> float:
            return self._mileage
        @mileage.setter    
        def mileage(self, mileage: int) -> None:
            if isinstance(mileage, int):
                if mileage >= 0: self._mileage = float(mileage)
        
        @property    
        def model(self) -> str:
            return self._model
        @model.setter    
        def model(self, model:str) -> None:
            self._model = str(model)
        
        @property    
        def price(self) -> float:
            return self._price
        @price.setter    
        def price(self, price: int):
            if isinstance(price, int):
                if price >= 0: self._price = price
            
        def common_init(self, model, make, mileage, price) -> None:
            self.make = make
            self.model = model
            self.mileage = mileage
            self.price = price
            
        def common_str(self, unique) -> str:
            return "Make:  "+str(self.make)+"  Model:  "+str(self.model)+"  Milage:  "+str(self.mileage)+"  Price:  "+str(self.price)+str(unique)


    class Car(_common):
        def __init__(self, model, make, mileage, price, doors) -> None:
            self.common_init(model, make, mileage, price)
            self.doors = doors

        @property    
        def doors(self) -> int:
            return self._doors
        @doors.setter    
        def doors(self, doors: int) -> None:
            if isinstance(doors, int):
                if doors > 0: self._doors = doors
                
        def __str__(self) -> str:
            return self.common_str(" Doors: "+str(self.doors))
            
    class SUV(_common):
        def __init__(self, model, make, mileage, price, pass_cap) -> None:
            self.common_init(model, make, mileage, price)
            self.pass_cap = pass_cap
        
        @property    
        def pass_cap(self) -> int:
            return self._pass_cap
        @pass_cap.setter    
        def pass_cap(self, pass_cap: int) -> None:
            if isinstance(pass_cap, int):
                if pass_cap > 0: self._pass_cap = pass_cap
                
        def __str__(self) -> str:
            return self.common_str(" pass cap: "+str(self.pass_cap))
            
    class Truck(_common):
        def __init__(self, model, make, mileage, price, drive_type) -> None:
            self.common_init(model, make, mileage, price)
            self.drive_type = drive_type
        
        @property    
        def drive_type(self) -> str:
            return self._drive_type
        @drive_type.setter    
        def drive_type(self, drive_type) -> str:
            if drive_type == "2WD" or drive_type == "4WD": self._drive_type = drive_type
            
        def __str__(self) -> str:
            return self.common_str(" drive type: "+str(self.drive_type))
      
        



























import os.path
import pickle

# This program creates a Car object, a Truck object,
# and an SUV object.
from Hacking_To_The_Gate import *
# Constants for the menu choices
NEW_CAR_CHOICE = 1
NEW_TRUCK_CHOICE = 2
NEW_SUV_CHOICE = 3
FIND_VEHICLE_CHOICE = 4
SHOW_VEHICLES_CHOICE = 5
QUIT_CHOICE = 6

filePath = "vehiclesList.pickle"

def create(vehicleType):
    try:
        j = [input("Model: "),int(input("Make: ")),int(input("Milage: ")),int(input("Price: "))]
        if not(j[1] >= 0 and j[2] >= 0 and j[3] >= 0): raise TypeError
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
    

def main():
    # Create empty list for vehicles
    vehicles_list = CheeseWheel()
    # Create a Car object for a used 2001 BMW
    # with 70,000 miles, priced at $15,000, with
    # 4 doors.
    #car = Vehicle.Car('BMW 320', 2001, 70000, 15000, 4)
    #vehicles_list.append(car)
    # Create a Truck object for a used 2002
    # Toyota pickup with 40,000 miles, priced
    # at $12,000, with 4-wheel drive.
    #truck = Vehicle.Truck('Toyota RAV4', 2002, 40000, 12000, '4WD')
    #vehicles_list.append(truck)
    # Create an SUV object for a used 2000
    # Volvo with 30,000 miles, priced
    # at $18,500, with 5 passenger capacity.
    #suv = Vehicle.SUV('Volvo XC60', 2010, 30000, 18500, 5)
    #vehicles_list.append(suv)
    choice = 0
    while choice != QUIT_CHOICE:
        # display the menu.
        display_menu()
        # Get the user's choice.
        try: choice = int(input('Enter your choice: '))
        except: choice = 7
        # Perform the selected action.
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
            #show all vehicles
            print('The following cars are in inventory:')
            for item in vehicles_list:
                print(item)
        elif choice == QUIT_CHOICE:
            print('Exiting the program...')
            MilkWheel(vehicles_list)
            exit()
        else:
            print('Error: invalid selection.')
# The display_menu function displays a menu.
def display_menu():
    print(' MENU')
    print('1) New car')
    print('2) New truck')
    print('3) New SUV')
    print('4) Find vehicles by make')
    print('5) Show all vehicles')
    print('6) Quit')
# Call the main function.
if __name__ == '__main__':
    main()