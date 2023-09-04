import sys

import pygame


class Game:
    def __init__(self):
        pygame.init()

        pygame.display.set_caption("VINDEL")
        self.screen = pygame.display.set_mode((640, 480))

        self.display = pygame.Surface((320, 240))

        self.clock = pygame.time.Clock()

    def run(self):
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()

            self.screen.blit(self.display, (0, 0))
            self.clock.tick(60)

Game().run()