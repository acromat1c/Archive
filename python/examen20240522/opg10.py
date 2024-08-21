def postfix(expression:str)->int:
    result = expression[0]
    for i in range(1,len(expression),2):
        try: result = eval(str(result)+expression[i+1]+expression[i])
        except: print("invalid postfix syntax"); exit()
    return result

print(postfix("17*9+3"))