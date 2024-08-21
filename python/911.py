from datetime import datetime, timedelta





class Flight():
    def __init__(self,flightNumber,departureTime,arrivalTime):
        self.flightNumber = flightNumber
        self.departureTime = departureTime
        self.arrivalTime = arrivalTime

    def getFlightTime(self):
        return self.arrivalTime - self.departureTime
    




class Itinerary():
    def __init__(self, flights):
        self.flights = flights
     
    def getTotalFlightTime(self):
        totalFlightTime = timedelta()
        for flight in self.flights:
            totalFlightTime = totalFlightTime + flight.getFlightTime()
        return totalFlightTime.total_seconds() / 60
        
    def getTotalTravelTime(self):
        return (self.flights[-1].arrivalTime - self.flights[0].departureTime).total_seconds() / 60
        




if __name__ == "__main__":
    flights = []

    flights.append(Flight("US230",datetime(2014, 4, 5, 5, 5, 0),datetime(2014, 4, 5, 6, 15, 0)))

    flights.append(Flight("US235",datetime(2014, 4, 5, 6, 55, 0),datetime(2014, 4, 5, 7, 45, 0)))

    flights.append(Flight("US237",datetime(2014, 4, 5, 9, 35, 0),datetime(2014, 4, 5, 12, 55, 0)))

    itinerary = Itinerary(flights)

    print(itinerary.getTotalTravelTime())
    

    print(itinerary.getTotalFlightTime())