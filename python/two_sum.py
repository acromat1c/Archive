from time import time
def main():




    def f(a:list[int]):
        o={}
        for ie, i in enumerate(a):
            if i in o:
                if o[i[0]]==0:o[i[0]]=1
            else:o[i]=0
        print(o)








    f([1,2,3,4,5,1,4,4])

start_time = time()
main()
end_time = time()
print("execution time:",start_time - end_time)