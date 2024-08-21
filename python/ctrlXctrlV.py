with open("text.txt","r+") as file:
    text = file.read()
    print(text,"\n")
with open("text.txt","w") as file:
    text = text.replace(input("what too replace: "),input("with what: "))
    print(text,"\n")
    file.write(text)