def bigMoneyMachinHyperMaxTrader3000000(THEmONEYlIST:list[int])->int:
    greedLayer4 = [0,0,0]
    for BIGmONEYiNDEX, MEGAmONEYvALUE in enumerate(THEmONEYlIST[:-1]):
        MINmONEY = min(THEmONEYlIST[BIGmONEYiNDEX+1:])
        MAXmONEY = MEGAmONEYvALUE - MINmONEY
        if MAXmONEY > greedLayer4[2]:
            greedLayer4[0] = BIGmONEYiNDEX
            greedLayer4[1] = THEmONEYlIST[BIGmONEYiNDEX+1:].index(MINmONEY)+BIGmONEYiNDEX+1
            greedLayer4[2] = MAXmONEY
    return greedLayer4


if __name__ == "__main__":
    import time
    import random
    days = []
    for i in range(100000):
        days.append(random.randrange(1,100))
    start_time = time.time()
    print(bigMoneyMachinHyperMaxTrader3000000(days))
    print("--- %s seconds ---" % (time.time() - start_time))