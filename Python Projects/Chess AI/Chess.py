import pygame
import ChessEngine

    
pygame.init()
WIDTH = HEIGHT = 512
DIMENSIONS = 8
SQ_SIZE = HEIGHT // DIMENSIONS
MAX_FPS = 15
IMAGES = {}

def loadImages():
    peices = ['wp', 'wR', 'wN', 'wB', 'wK', 'wQ', 'bp', 'bR', 'bN', 'bB', 'bK', 'bQ']
    for peice in peices:
        IMAGES[peice] = pygame.transform.scale(pygame.image.load(peice + ".png"), (SQ_SIZE, SQ_SIZE))


def main():
    SCREEN = pygame.display.set_mode((WIDTH, HEIGHT))
    clock = pygame.time.Clock()
    SCREEN.fill(pygame.Color("white"))
    gs = ChessEngine.GameState()
    validMoves = gs.getValidMoves()
    moveMade = False #flag variable to let us know when to check for possible moves
    loadImages()
    running = True
    sqSelected = ()
    playerClicks = []
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.MOUSEBUTTONDOWN:
                location = pygame.mouse.get_pos()
                col = location[0]//SQ_SIZE
                row = location[1]//SQ_SIZE
                if sqSelected == (row, col):
                    sqSelected = ()
                    playerClicks = []
                else:
                    sqSelected = (row, col)
                    playerClicks.append(sqSelected)
                if len(playerClicks) == 2:
                    move = ChessEngine.Move(playerClicks[0], playerClicks[1], gs.board)
                    print(move.getChessNotation())
                    if move in validMoves:
                        gs.makeMove(move)
                        moveMade = True
                        print(gs.whiteToMove)
                    sqSelected = ()
                    playerClicks = []
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_z:
                    gs.undoMove()
                    moveMade = True

        if moveMade:
            validMoves = gs.getValidMoves()
            moveMade = False
        drawGameState(SCREEN, gs)
        clock.tick(MAX_FPS)
        pygame.display.flip()

def drawGameState(screen, gs):
    drawBoard(screen)
    drawPeices(screen, gs.board)
    


def drawBoard(screen):
    colors = [pygame.Color("white"), pygame.Color("grey")]
    for r in range(DIMENSIONS):
        for c in range(DIMENSIONS):
            color = colors[((r+c)%2)]
            pygame.draw.rect(screen, color, pygame.Rect(c*SQ_SIZE, r*SQ_SIZE, SQ_SIZE, SQ_SIZE))


def drawPeices(screen, board):
    for r in range(DIMENSIONS):
        for c in range(DIMENSIONS):
            peice = board[c][r]
            if peice != "--":
                screen.blit(IMAGES[peice], pygame.Rect(r*SQ_SIZE, c*SQ_SIZE, SQ_SIZE, SQ_SIZE))


if __name__ == "__main__":
    main()