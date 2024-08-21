from datetime import datetime

class SpeedTicket():
        def __init__(self,registryNumber,time,speed,speedLimit):
            self.registryNumber = registryNumber
            self.time = time
            self.speed = speed
            self.speedLimit = speedLimit
        def __str__(self):
            return "registryNumber:"+str(self.registryNumber)+" time:"+str(self.time)+" speed:"+str(self.speed)+" speed_limit:"+str(self.speedLimit)

def fileToDictionary(file: str) -> list[str]:
    fileDict = {}
    for entity in file.split("\n"):
        fileDict[entity[0:7]] = datetime(int(entity[9:13]),int(entity[14:16]),int(entity[17:19]),int(entity[20:22]),int(entity[23:25]),int(entity[26:28]))
    return fileDict

def listSpeeders(filenameA,filenameB,speedLimit,distance):
    speeders = {}
    ticketLimit = (distance/speedLimit)*3600*1.05
    for entity in filenameA:
        if entity in filenameA and entity in filenameB:
            avgSpeed = (filenameB[entity]-datetime(1970,1,1)).total_seconds()-(filenameA[entity]-datetime(1970,1,1)).total_seconds()
            if  avgSpeed > ticketLimit:
                speeders[entity] = (filenameA[entity], avgSpeed)
    return speeders

def checkForSpeeding(file1,file2,speedLimit,distance):
    with open(file1,"r+") as file:
        boxA = fileToDictionary(file.read())
    with open(file2,"r+") as file:
        boxB = fileToDictionary(file.read())
    return listSpeeders(boxA,boxB,speedLimit,distance)