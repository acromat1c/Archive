with open(input("file path: "),"r+") as file:
    string = file.read()
    keywords = ["and","as","assert","break","class","continue","def","del","elif","else","except","False","finally","for","from","global","if","import","in","is","lambda","None","nonlocal","not","or","pass","raise","return","True","try","while","with","yield"]
    count = {}
    for keyword in keywords:
        counter = string.count(str(keyword))
        if counter != 0:
            count[keyword] = counter
    print(count)