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