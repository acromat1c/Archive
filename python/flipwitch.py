def reverse(string):
    global value
    value = ""
    
    def reverseReverse(string):  
        global value
        if len(string) == 0:
            return
        temp = string[0]
        reverse(string[1:])
        value += temp
        
    reverseReverse(str(string))
    return value

# unit test
if __name__ == "__main__":
    print(reverse(12345))
    print(reverse(64223423))
    print(reverse(15543223))
    print(reverse(987654321))
    print(reverse(23411471))
    print(reverse("ewdfsg"))
    print(reverse(134321.6564))