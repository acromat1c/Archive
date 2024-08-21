class chess():
    def __init__(self):
        self.reset()
    def reset(self):
        self.board=[[0 for i in range(8)]for i in range(8)]
        self.boardMirror=[[0 for i in range(8)]for i in range(8)]
        self.danger = False
        self.queens=0
    def placeQueen(self,x,y):
        try:
            if(x<=0 or x>=9 or y<=0 or y>=9):raise()
            self.board[y-1][x-1]=1
        except:print("invalid queen placement")
    def removeQueen(self,x,y):
        try:
            if(x<=0 or x>=9 or y<=0 or y>=9):raise()
            self.board[y-1][x-1]=0
        except:print("invalid queen removal")
    def sightlines(self):
        self.queens=0
        for i,n in enumerate(self.board):
            for j,n in enumerate(self.board[i]):
                if(self.board[i][j]==1):
                    self.queens+=1
                    for im,n in enumerate(self.board):
                        for jm,n in enumerate(self.board[i]):
                            if(im==i and jm==j):continue
                            elif(im==i or jm==j or im-i==jm-j or -im+i==jm-j):self.boardMirror[im][jm]=1
                            if(self.boardMirror[im][jm]==1 and 1==self.board[im][jm]):self.danger=True
    def printBoard(self, showSightline):
        try:bool(showSightline)
        except:showSightline=False
        endSym=" "
        for i,n in enumerate(self.board):
            for j,n in enumerate(self.board[i]):
                if(n==1):
                    if(self.boardMirror[i][j]==1 and showSightline):print("O",end=endSym)
                    else:print("Q",end=endSym)
                elif(self.boardMirror[i][j]==1 and showSightline):print("X",end=endSym)
                elif(n==0):
                    if(i%2==0 and j%2==0 or (i+1)%2==0 and (j+1)%2==0):print("▒",end=endSym)
                    else:print("▓",end=endSym)
                else:print(n,end=endSym)
            print()
        print()
    def run(self):
        self.sightlines()
        self.printBoard(True)
        if(self.danger):print("you lose. blood has been spilt across the lands, tear shead and lives lost('p' to reset board)")
        elif(self.queens==0):print("nothing happends. you win no glory, but no one dies either('p' to reset board)")
        elif(self.queens==1):print("you win. you have saved the kingdom and acquired a",
                   " beautiful queen as wife! play again and see if you can increase your high score('p' to reset board)\n")
        elif(self.queens==8):print("you win. you have saved the kingdom and earned yourself a personal harem of  8 ",
                   " beautiful queens! You have gotten the highes posible score, impressive!\n")
        else:print("you win. you have saved the kingdom and earned yourself a personal harem of ",self.queens,
                   " beautiful queens! play again and see if you can expand it even further('p' to reset board)\n")
        self.reset

class cmd():
    def __init__(self):
        try:
            self.chessInstanse = chess()
            self.main()
        except:print("cmd error")
    def strToInput(self,ui):
        ui.replace(" ","")
        firstComma = ui.find(",")
        lastComma = ui.rfind(",")
        if(firstComma==lastComma):return([ui[0],0,0])
        return([ui[0],int(ui[firstComma+1:lastComma]),int(ui[lastComma+1:])])
    def main(self):
        print(" ▄▄▄ .▪   ▄▄ •  ▄ .▄▄▄▄▄▄    .▄▄▄  ▄• ▄▌▄▄▄ .▄▄▄ . ▐ ▄ .▄▄ ·\n",
              "▀▄.▀·██ ▐█ ▀ ▪██▪▐█•██      ▐▀•▀█ █▪██▌▀▄.▀·▀▄.▀·•█▌▐█▐█ ▀. \n",
              "▐▀▀▪▄▐█·▄█ ▀█▄██▀▐█ ▐█.▪    █▌·.█▌█▌▐█▌▐▀▀▪▄▐▀▀▪▄▐█▐▐▌▄▀▀▀█▄\n",
              "▐█▄▄▌▐█▌▐█▄▪▐███▌▐▀ ▐█▌·    ▐█▪▄█·▐█▄█▌▐█▄▄▌▐█▄▄▌██▐█▌▐█▄▪▐█\n",
              " ▀▀▀ ▀▀▀·▀▀▀▀ ▀▀▀ · ▀▀▀     ·▀▀█.  ▀▀▀  ▀▀▀  ▀▀▀ ▀▀ █▪ ▀▀▀▀ \n",
              "*Eight Queens*\n in this game your gole is to place 8 queens on a chess board in a maner where they are",
              " all safe from attack. use your head and solve this daunting puzzle\nif unsure try '?'")
        self.chessInstanse.printBoard(False)
        while True:
            try:
                ui=self.strToInput(input("$ "))
            except:continue
            if(ui[0] == "?"):print("list of commands:\n",
                                   "command function|syntax|example\n",
                                   "place queen|e,int(x),int(y)|e,3,2\n",
                                   "remove queen|r,int(x),int(y)|r,3,2\n",
                                   "reset board|p|p\ncheck solution|c|c")
            elif(ui[0]=="c"):self.chessInstanse.run()
            elif(ui[0]=="p"):
                self.chessInstanse.reset()
                self.chessInstanse.printBoard(False)
            elif(ui[0]=="e" and ui[1]!=0):
                self.chessInstanse.placeQueen(ui[1],ui[2])
                self.chessInstanse.printBoard(False)
            elif(ui[0]=="r" and ui[1]!=0):
                self.chessInstanse.removeQueen(ui[1],ui[2])
                self.chessInstanse.printBoard(False)

if __name__ == "__main__":
    user = cmd()