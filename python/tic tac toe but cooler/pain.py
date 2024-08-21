# main.py
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
            








# tic_tac_toe_but_cooler.py
class TicTacToe():
    
    class Symbols:
        X = "X"
        O = "O"
        E = " "

    def __init__(self):
        self.reset()
    
    @property
    def board(self) -> list[str]:
        return self._board
    
    def reset(self):
        self._board = [TicTacToe.Symbols.E for _ in range(9)]

    def printBoard(self):
        print(self._board[0],"|",self._board[1],"|",self._board[2],"\n",
              "-----\n",
              self._board[3],"|",self._board[4],"|",self._board[5],"\n",
              "-----\n",
              self._board[6],"|",self._board[7],"|",self._board[8],
              sep="")
        
    def place(self, x: int, y: int, symbol: Symbols) -> bool: 
            try:
                x = int(x)
                y = int(y)
                if not (0 <= y <= 2 or 0 <= x <= 2): raise ValueError
                if not(self._board[y*3+x] == TicTacToe.Symbols.E): raise BoardError
                if symbol not in [TicTacToe.Symbols.X,TicTacToe.Symbols.O]: raise NameError
            except ValueError: print("both x and y must be integers and be between 0 and 2")
            except NameError: print("the selected symbal is invalid")
            except Exception as BoardError: print("the selected space on the board is invalid")
            else:
                self._board[y*3+x] = symbol
                return True
            finally: return False
    
    def win(self) -> str:
        if TicTacToe.Symbols.E not in [*self._board[0],*self._board[1],*self._board[2]]: return TicTacToe.Symbols.E
        if self._board[0]==self._board[4]==self._board[8] and self._board[4]!=" ": return self._board[4]
        if self._board[6]==self._board[4]==self._board[2] and self._board[4]!=" ": return self._board[4]
        for i in range(3):
            if self._board[i]==self._board[3+i]==self._board[6+i] and self._board[i]!=" ": return self._board[i]
            if self._board[i*3]==self._board[i*3+1]==self._board[i*3+2] and self._board[i*3]!=" ": return self._board[i*3]
            
                

            

if __name__ == "__main__":         
    t = TicTacToe()
    t.printBoard
    while True: 
        for i in [TicTacToe.Symbols.X, TicTacToe.Symbols.O]:
            print("player", i, "turn:")
            t.place(input("x: "),input("y: "),i)
            t.printBoard()
            if j := t.win() :
                if j == TicTacToe.Symbols.E: "draw"
                else: print("the winner is",j)
                t.reset()
                t.printBoard()
                break
            








# ai.py
from random import choice
from copy import deepcopy

class Ai():
     
    def gridConvert(self,action):
        return action % 3, int(action / 3)

    def readBoard(self, board: list[str],symbolEmpty=0,symbolAi=1,symbolPlayer=-1) -> list[list[int],list[int]]:
        aiBoard = []
        possibleMoves =[]
        for ie, i in enumerate(board):
            if i == symbolEmpty: 
                aiBoard.append(0)
                possibleMoves.append(ie)
            elif i == symbolPlayer: aiBoard.append(-1)
            elif i == symbolAi: aiBoard.append(1)
        return aiBoard, possibleMoves
     
    def winCondition(self, board:list) -> int:
        for i in range(3):
            if board[i]==board[i+3]==board[i+6] and board[i] != 0:return board[i]
            if board[i*3]==board[i*3+1]==board[i*3+2] and board[i*3] != 0:return board[i*3]
        if board[0]==board[4]==board[8] or board[2]==board[4]==board[6] and board[4] != 0:return board[4]
        return 0

    def miniMax(self, board: list[list[int],list[int]],maxLayers=5, _turn=1, _topLayer=True, _layer=0) -> int:
        if maxLayers <= 0: return "maxLayers must a least be 1"
        if _layer >= maxLayers:
            return -1 / _layer

        if not _topLayer and (len(board[1]) == 0 or self.winCondition(board[0]) != 0):
            return self.winCondition(board[0]) / _layer

        if _topLayer:
            possibleMoves = []
        bestMove = -1

        for move in board[1]:
            boardCopy = deepcopy(board)
            boardCopy[0][move] = _turn
            boardCopy[1].remove(move)
            if _turn == 1: currentMove = self.miniMax(boardCopy, _turn=-1, _topLayer=False, _layer=_layer+1)
            else: currentMove = self.miniMax(boardCopy, _topLayer=False, _layer=_layer+1)
            if _topLayer:
                if currentMove == bestMove: possibleMoves.append(move)
                elif currentMove > bestMove: 
                    possibleMoves = [move]
                    bestMove = currentMove
            else:
                bestMove = currentMove

        if _topLayer: return possibleMoves
        else: return bestMove
        
    def play(self, board: list[str],symbolEmpty=0,symbolAi=1,symbolPlayer=-1, level=5, grid=False):
        i = lambda: choice(self.miniMax(self.readBoard(board,symbolEmpty=symbolEmpty,symbolAi=symbolAi,symbolPlayer=symbolPlayer)))
        if grid: return self.gridConvert(i())
        else: return i()





if __name__ == "__main__":
    ai = Ai()
    print(ai.play(["O"," "," "," ","X","O","X"," ","X"],symbolEmpty=" ", symbolAi="O", symbolPlayer="X"))
    print(ai.miniMax(ai.readBoard(["O"," ","O"," ","X"," ","X"," ","X"],symbolEmpty=" ", symbolAi="O", symbolPlayer="X")))
    print(ai.miniMax(ai.readBoard(["O"," ","O"," ","O"," "," ","X","X"],symbolEmpty=" ", symbolAi="O", symbolPlayer="X")))
    print(ai.miniMax(ai.readBoard([" "," ","O"," "," "," ","X","X"," "],symbolEmpty=" ", symbolAi="O", symbolPlayer="X")))
    print(ai.miniMax(ai.readBoard([" "," "," "," "," "," "," "," "," "],symbolEmpty=" ", symbolAi="O", symbolPlayer="X")))
    print(ai.miniMax(ai.readBoard(["X","X","X","X","X","X","X","X","X"],symbolEmpty=" ", symbolAi="O", symbolPlayer="X")))