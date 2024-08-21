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