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