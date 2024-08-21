from datetime import datetime

def test1():
    account1 = Account(1, 1000, 50000, 7)
    print(account1)
    account1.deposit(500)
    print(f'New balance after depositing 500 is {account1.getBalance()}')
    account1.withdraw(1000)
    print(f'New balance after withdrawal of 1000 is {account1.getBalance()}')

def test2():
    account2 = Account(1, 1000, 50000, 7)
    print(account2)
    account2.deposit(500)
    print(f'New balance after depositing 500 is {account2.getBalance()}')
    account2.withdraw(1000)
    print(f'New balance after withdrawal of 10000 is {account2.getBalance()}')
    account2.showTransactions()

class Account():
    def __init__(self,i,n,b,t):
        try:
            self.__ID = i
            self.__accountNo = int(n)
            self.__balance = float(b)
            self.__interest = float(t)
            self.__transactions = []
        except:print("user error, please retry account registration")
    def getBalance(self):
        return(self.__balance)
    def deposit(self,amount):
        self.__transactions.append(Transaction(amount))
        self.__balance+=amount
    def withdraw(self,amount):
        self.__transactions.append(Transaction(amount*-1))
        if (self.__balance-amount>0):self.__balance-=amount
    def showTransactions(self):
        for i in self.__transactions:
            print(i)
    def __str__(self):
        return("ID: "+str(self.__ID)+"\n"+
               "account number: "+str(self.__accountNo)+"\n"+
               "balance: "+str(self.__balance)+"\n"+
               "interest: "+str(self.__interest))

class Transaction():
    def __init__(self,amount):
        self.__time = datetime.now()
        self.__amount = amount
    def getTimeAsStr(self):
        return(str(self.__time.strftime("%Y/%m/%d, %H:%M:%S")))
    def getTime(self):
        return(self.__time)
    def getAmount(self):
        return(self.__amount)
    def __str__(self):
        return("Time: "+self.getTimeAsStr()+" ||| "+
               "amount: "+str(self.__amount))
test1()
print("\n")
test2()