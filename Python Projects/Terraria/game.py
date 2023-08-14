import sys

import pygame

pygame.init()

pygame.display.set_caption("Pyarria Vindle Edition")
screen = pygame.display.set_mode((640, 480))

clock = pygame.time.Clock()

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    pygame.display.update()
    clock.tick(60)