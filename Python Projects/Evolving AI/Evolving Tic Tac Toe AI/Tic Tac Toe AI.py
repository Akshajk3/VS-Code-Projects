import pygame
import neat
import os
import random

pygame.font.init()
pygame.init

SCREEN_WIDTH = 480
SCREEN_HEIGHT = 480
SCREEN = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Tic Tac Toe AI")

X_IMG = pygame.image.load(os.path.join("X.png"))
O_IMG = pygame.image.load(os.path.join("O.png"))
BOARD_IMG = pygame.image.load(os.path.join("Toc.png"))


class Toc:
    X_POS = 240
    Y_POS = 240

    def __init__(self, img=BOARD_IMG):
        self.img = BOARD_IMG


    def draw(self):
        SCREEN.blit(self.image, (self.X_POS, self.Y_POS))

def main():
    clock = pygame.time.Clock()

    board = [Toc()]

    run = True
    
    while run:
        for toc in board:
            toc.draw()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
        
        SCREEN.fill((255, 255, 255))

        clock.tick(30)
        pygame.display.update()

main()