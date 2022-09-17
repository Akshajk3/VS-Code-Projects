class GameState():
    def __init__(self):
        #First letter represents the color, b for black, and w for white
        #The second letter represents the peice
        #"--" represents a blank space
        self.board = [
            ["bR", "bN", "bB", "bQ", "bK", "bB", "bN", "bR"],
            ["bp", "bp", "bp", "bp", "bp", "bp", "bp", "bp"],
            ["--", "--", "--", "--", "--", "--", "--", "--"],
            ["--", "--", "--", "--", "--", "--", "--", "--"],
            ["--", "--", "--", "--", "--", "--", "--", "--"],
            ["--", "--", "--", "--", "--", "--", "--", "--"],
            ["wp", "wp", "wp", "wp", "wp", "wp", "wp", "wp"],
            ["wR", "wN", "wB", "wQ", "wK", "wB", "wN", "wR"]
            ]
        self.whiteToMove = True
        self.moveLog = []
    '''
    Takes a move as a parameter and executes it(Does not work for castling, pawn promotion and en-passant'''
    def makeMove(self, move):
        self.board[move.startRow][move.startCol] = "--"
        self.board[move.endRow][move.endCol] = move.pieceMoved
        self.moveLog.append(move)
        self.whiteToMove = not self.whiteToMove
    
    def undoMove(self):
        if len(self.moveLog) != 0:
            move = self.moveLog.pop()
            self.board[move.startRow][move.startCol] = move.pieceMoved
            self.board[move.endRow][move.endCol] = move.pieceCaptured
            self.whiteToMove = not self.whiteToMove
    '''
    All moves considering check
    '''
    def getValidMoves(self):
        return self.getAllPossibleMoves()#for now we will not worry about checks
    '''
    All moves without considering check
    '''
    def getAllPossibleMoves(self):
        moves = []
        for r in range(len(self.board)):#number of rows
            for c in range(len(self.board[r])):#number of collumns
                turn = self.board[r][c][0]
                if(turn == "w" and self.whiteToMove) and (turn == "b" and not self.whiteToMove):
                    piece = self.board[r][c][1]
                    if piece == "p":
                        self.getPawnMoves(r, c, moves)
                    elif piece == "r":
                        self.getRookMoves(r, c, moves)

    '''
    Get all possible pawn moves for the pawn located at r, c and add these moves to the list
    '''
    def getPawnMove(self, r, c, moves):
        pass

    '''
    Get all possible rook moves for the rook located at r, c and add these moves to the list
    '''
    def getRookMoves(self, r, c, moves):
        pass




class Move():

    ranksToRows = {"1": 7, "2": 6, "3": 5, "4": 4, "5": 3, "6": 2, "7": 1, "8": 0}
    rowsToRanks = {v: k for k, v in ranksToRows.items()}
    filesToCols = {"a": 0, "b": 1, "c": 2, "d": 3, "e": 4, "f": 5, "g": 6, "h": 7}
    colsToFiles = {v: k for k, v in filesToCols.items()}


    def __init__(self, startSq, endSq, board):
        self.startRow = startSq[0]
        self.startCol = startSq[1]
        self.endRow = endSq[0]
        self.endCol = endSq[1]
        self.pieceMoved = board[self.startRow][self.startCol]
        self.pieceCaptured = board[self.endRow][self.endCol]

    def getChessNotation(self):
        return self.getRankFile(self.startRow, self.startCol) + self.getRankFile(self.endRow, self.endCol)

    def getRankFile(self, r, c):
        return self.colsToFiles[c] + self.rowsToRanks[r]
