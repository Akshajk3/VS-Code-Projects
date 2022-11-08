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
    def __init__(self, x_pos, y_pos):
        self.rect = pygame.draw.rect()


def update_ui(COLOR):
    board = Toc()
    SCREEN.fill((255, 255, 255))
    
    board.draw()
    

def main():
    run = True
    toc = Toc()

    while run:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

            update_ui(RED)
            pygame.display.update()


if __name__ == "__main__":
    main()