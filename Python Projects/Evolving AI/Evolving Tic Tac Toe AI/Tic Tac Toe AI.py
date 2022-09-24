import pygame
#import neat
import os
import random

pygame.font.init()
pygame.init

SCREEN_WIDTH = 480
SCREEN_HEIGHT = 480
SCREEN = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Tic Tac Toe AI")

font = pygame.font.SysFont('arial', 25)

X_IMG = pygame.image.load(os.path.join("X.png"))
O_IMG = pygame.image.load(os.path.join("O.png"))
BOARD_IMG = pygame.image.load(os.path.join("Toc.png"))

IMG_SIZE = (150, 150)

X_IMG = pygame.transform.scale(X_IMG, IMG_SIZE)

TILES = []

GREEN = (0, 255, 0)
RED = (255, 0, 0)
COLORS = GREEN

POS_X = [90, 215, 340]
POS_Y = [90, 90, 90]

DRAW = False

class Toc:
    X_POS = 50
    Y_POS = 50

    def __init__(self, img=BOARD_IMG):
        self.img = img

    def draw(self):
        SCREEN.blit(self.img, (self.X_POS, self.Y_POS))
        

class Tile:

    def __init__(self):
        self.positions = [(90, 90), (215, 90), (340, 90)]
        i = 0
        while i < 3:
            TILES[i] = pygame.draw.rect(SCREEN, COLORS, (POS_X[i], POS_Y[i], 30, 30))
            i += 1


    def draw(self, COLOR, draw):
        i = 0
        if DRAW == False:
            while i < 3:
                tileDraw[i] = True
                pygame.draw.rect(SCREEN, COLOR, (POS_X[i], POS_Y[i], 30, 30))
                for event in pygame.event.get():
                    if pygame.rect.collidepoint(pygame.mouse.get_pos()):
                        COLOR = RED
                        if event.type == pygame.MOUSEBUTTONDOWN:
                            draw = True
                    else:
                        COLOR = GREEN
                i += 1
        

class X:
    
    def __init__(self, img=X_IMG):
        self.img = img
        self.X_POS = 0
        self.Y_POS = 0
    
    def draw(self):
        SCREEN.blit(self.img, (30, 50))

def update_ui(COLOR):
    board = Toc()
    tile = Tile()
    XP = X()
    SCREEN.fill((255,255,255))
    board.draw()
    tile.draw(COLORS, DRAW)
    if DRAW == True:
        XP.draw()

def main():
    global positions, tileDraw

    clock = pygame.time.Clock()

    tileDraw = [False, False, False]

    player = Toc()
    X_P = X()
    tile = Tile()

    run = True
    
    while run:

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

        
        update_ui(COLORS)
        clock.tick(30)
        pygame.display.update()

main()