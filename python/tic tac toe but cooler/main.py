from ai import *
from tic_tac_toe_but_cooler import *

if __name__ == "__main__":
    t = TicTacToe()
    ai = Ai()
    player = TicTacToe.Symbols.X
    while True:
        for i in [TicTacToe.Symbols.X, TicTacToe.Symbols.O]:
            print("player", i, "turn:")
            if i == player: t.place(input("x: "),input("y: "),i)
            else: 
                x, y = ai.play(t.board,symbolEmpty=" ", symbolAi="O", symbolPlayer="X",grid=True)
                print("x: ",x,"\ny: ",y,sep="")
                t.place(x,y,i)
            t.printBoard()
            if j := t.win() :
                if j == TicTacToe.Symbols.E: "draw"
                else: print("the winner is",j,"\n")
                if player == TicTacToe.Symbols.X: player = TicTacToe.Symbols.O
                else: player = TicTacToe.Symbols.X
                t.reset()
                t.printBoard()
                break