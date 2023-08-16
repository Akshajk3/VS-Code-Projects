import sys

import pygame


class Game:
    def __init__(self):
        pygame.init()

        pygame.display.set_caption("GAME IDK")
        self.screen = pygame.display.set_mode((640, 480))

        self.display = pygame.Surface((320, 240))