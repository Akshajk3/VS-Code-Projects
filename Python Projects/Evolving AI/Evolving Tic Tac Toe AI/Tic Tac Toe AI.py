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

BOX_SIZE = 30

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

class Piece:
    def __init__(self):
        self.X_img = X_IMG
        self.O_img = O_IMG
        self.X_turn = True
    
    def draw(self, x_pos, y_pos):
        SCREEN.blit(self.X_img, (x_pos, y_pos))

class Tile:
    def __init__(self):
        self.x_pos = 90
        self.y_pos = 90
        self.rect = pygame.Rect(self.x_pos, self.y_pos, BOX_SIZE, BOX_SIZE)
        self.color = GREEN
        self.touching = False
        self.piece = Piece()
        self.placed = False

    def input(self):
        if self.rect.collidepoint(pygame.mouse.get_pos()):
            self.color = RED

    def checkForPress(self):
        for event in pygame.event.get():
            if event.type == pygame.MOUSEBUTTONDOWN:
                print("Hello")

    def draw(self):
        if self.placed == True:
            self.piece.draw(self.x_pos, self.y_pos)
        else:
            pygame.draw.rect(SCREEN, self.color, self.rect)


def update_ui():
    board = Toc()
    tile = Tile()
    SCREEN.fill((255, 255, 255))

    tile.input()
    tile.checkForPress()
    
    board.draw()
    tile.draw()
    

def main():
    run = True
    toc = Toc()

    while run:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

            update_ui()
            pygame.display.update()


if __name__ == "__main__":
    main()