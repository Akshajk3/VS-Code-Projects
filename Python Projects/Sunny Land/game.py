import sys

import pygame

from scripts.utils import load_image

class Game:
    def __init__(self):
        pygame.init()

        pygame.display.set_caption("VINDEL")
        self.screen = pygame.display.set_mode((640, 480))

        self.display = pygame.Surface((320, 240))

        self.clock = pygame.time.Clock()

        self.background = load_image('Background/Yellow.png')
        self.background = pygame.transform.scale(self.background, (640, 480))

    def run(self):
        self.display.blit(self.background,  (0, 0))

        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()

            self.screen.blit(pygame.transform.scale(self.display, self.screen.get_size()), (0, 0))
            pygame.display.update()
            self.clock.tick(60)

Game().run()