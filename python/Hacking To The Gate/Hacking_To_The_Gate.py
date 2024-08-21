from breaking_the_law import SpeedTicket

class Vehicle():

    class _common():
        def tickets(self):
            return self.ticketsList
        def registerTicket(self,time,speed,speedLimit):
            self.ticketsList.append(SpeedTicket(self.registryNumber,time,speed,speedLimit))

        @property    
        def make(self) -> int:
            return self._make
        @make.setter    
        def make(self, make: int) -> None:
            if isinstance(make,int):
                if make >= 0: self._make = make
        
        @property    
        def mileage(self) -> int:
            return self._mileage
        @mileage.setter    
        def mileage(self, mileage: int) -> None:
            if isinstance(mileage, int):
                if mileage >= 0: self._mileage = mileage
        
        @property    
        def model(self) -> str:
            return self._model
        @model.setter    
        def model(self, model:str) -> None:
            self._model = str(model)
        
        @property    
        def price(self) -> int:
            return self._price
        @price.setter    
        def price(self, price: int):
            if isinstance(price, int):
                if price >= 0: self._price = price
                
        @property    
        def registryNumber(self) -> int:
            return self._registryNumber
        @registryNumber.setter    
        def registryNumber(self, registryNumber: int):
                if len(registryNumber) == 7:
                    self._registryNumber = registryNumber
            
        def common_init(self, model, make, mileage, price, registryNumber) -> None:
            self.make = make
            self.model = model
            self.mileage = mileage
            self.price = price
            self.registryNumber = registryNumber
            self.ticketsList = []
            
        def common_str(self, unique) -> str:
            return "registryNumber:"+str(self.registryNumber)+" Model:"+str(self.model)+" Make:"+str(self.make)+" Milage:"+str(self.mileage)+" Price:"+str(self.price)+str(unique)


    class Car(_common):
        def __init__(self, registryNumber, model, make, mileage, price, doors) -> None:
            self.common_init(model, make, mileage, price, registryNumber)
            self.doors = doors

        @property    
        def doors(self) -> int:
            return self._doors
        @doors.setter    
        def doors(self, doors: int) -> None:
            if isinstance(doors, int):
                if doors >= 0: self._doors = doors
                
        def __str__(self) -> str:
            return self.common_str(" Doors:"+str(self.doors))
            
    class SUV(_common):
        def __init__(self, registryNumber, model, make, mileage, price, pass_cap) -> None:
            self.common_init(model, make, mileage, price, registryNumber)
            self.pass_cap = pass_cap            

        @property    
        def pass_cap(self) -> int:
            return self._pass_cap
        @pass_cap.setter    
        def pass_cap(self, pass_cap: int) -> None:
            if isinstance(pass_cap, int):
                if pass_cap >= 0: self._pass_cap = pass_cap
                
        def __str__(self) -> str:
            return self.common_str(" pass_cap:"+str(self.pass_cap))
            
    class Truck(_common):
        def __init__(self, registryNumber, model, make, mileage, price, drive_type) -> None:
            self.common_init(model, make, mileage, price, registryNumber)
            self.drive_type = drive_type         

        @property    
        def drive_type(self) -> str:
            return self._drive_type
        @drive_type.setter    
        def drive_type(self, drive_type) -> str:
            if drive_type == "2WD" or drive_type == "4WD": self._drive_type = drive_type
            
        def __str__(self) -> str:
            return self.common_str(" drive_type:"+str(self.drive_type))