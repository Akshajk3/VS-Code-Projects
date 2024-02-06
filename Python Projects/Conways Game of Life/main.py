import pygame
import numpy

pygame.init()

pygame.display.set_mode((800, 600))
pygame.display.set_caption("Videls Game of Life")

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

class GameOfLife:
    def __init__(self):
        pass

def main():
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()

        pygame.display.flip()

main()