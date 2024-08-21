#GUI.py
from calculator import Calculator
from tkinter import *
import threading as th





c = Calculator()
w = Tk()





def runtime():
    if len(e1.get()) > 1:
        e1.delete(1, END)
    if e1.get() not in set("+-*/"):
        e1.delete(0, END)
    for ie, i in enumerate(list(e0.get())):
        if i not in set("1234567890."):
            e0.delete(ie,END)
    for ie, i in enumerate(list(e2.get())):
        if i not in set("1234567890."):
            e2.delete(ie,END)
    w.after(5,runtime)

def calculateCall():
    if e0.get() != "" and e1.get() != "" and e2.get() != "":
       if e0.get()[0] != "." and e2.get()[0] != ".":
            c.calculate(float(e0.get()),float(e2.get()),str(e1.get()))
            lf = lambda l: "".join(l[0:-1])+"="+l[-1]
            lb.insert(0,lf(c.get_last_logged()))
            l4.config(text=c.get_last_logged()[-1])
            clearEntry()

def clearLogCall():
    c.clear_log()
    lb.delete(0,END)
    l4.config(text="")
    clearEntry()

def clearEntry():
    e0.delete(0,END)
    e1.delete(0,END)
    e2.delete(0,END)





l0 = Label(w,text="Operand 1")
l1 = Label(w,text="Operator(*-*/)")
l2 = Label(w,text="Operand 2")
l3 = Label(w,text="Result")
l4 = Label(w,text="")
l5 = Label(w,text="Log:")

e0 = Entry(w,width=20)
e1 = Entry(w,width=1)
e2 = Entry(w,width=20)

b0 = Button(w,text="Calculate",padx=15,pady=5,command=calculateCall)
b1 = Button(w,text="Clear log",padx=15,pady=5,command=clearLogCall)
b2 = Button(w,text="Quit",padx=15,pady=5,command=exit)

lb = Listbox(w)





l0.grid(column=0,row=0)
l1.grid(column=0,row=1)
l2.grid(column=0,row=2)
l3.grid(column=0,row=3)
l4.grid(column=1,row=3,columnspan=2)
l5.grid(column=0,row=5,columnspan=3)

e0.grid(column=1,row=0,columnspan=2)
e1.grid(column=1,row=1,columnspan=2)
e2.grid(column=1,row=2,columnspan=2)

b0.grid(column=0,row=4)
b1.grid(column=1,row=4)
b2.grid(column=2,row=4)

lb.grid(column=0,row=6,columnspan=3,padx=5,pady=5,sticky='nsew')





th.Thread(target=runtime, daemon=True).start()
w.mainloop()











#calculator.py
class Calculator:
    def __init__(self):
        self.clear_log()
    def calculate(self,operand1:float or int,operand2:float or int,operator:str):
       if operator == "+" or operator == "-" or operator == "*" or operator == "/":
            match operator:
                case "+":
                    result=operand1+operand2
                case "-":
                    result=operand1-operand2
                case "*":
                    result=operand1*operand2
                case "/":
                    result=operand1/operand2
            self.log.append([str(operand1),str(operator),str(operand2),str(result)])
    def get_log(self):
        return self.log
    def get_last_logged(self):
        return self.log[-1]
    def clear_log(self):
        self.log = []

def main():
    calculator = Calculator()
    calculator.calculate(1,2,'+')
    calculator.calculate(2,2,'*')
    calculator.calculate(16,2,'/')
    print(calculator.get_log())
    print(calculator.get_last_logged())

if __name__ == "__main__":
    main()