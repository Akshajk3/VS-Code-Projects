import pygame
import sys

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BACKGROUND_COLOR = (76, 76, 76)

class Raycaster:
    def __init__(self):
        pygame.init()

        pygame.display.set_caption("VindelPyCaster")
        self.screen = pygame.display.set_mode((1024, 512))

        self.mapX = 8
        self.mapY = 8
        self.mapS = self.mapX * self.mapY
        self.map = [
            1, 1, 1, 1, 1, 1, 1, 1,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
        ]

    def run(self):
        while True:

            self.screen.fill(BACKGROUND_COLOR)
            self.drawMap2D()

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()

            pygame.display.update()

    def drawMap2D(self):
        x = 0
        y = 0
        xo = 0
        yo = 0
        color = BLACK
        for y in range(self.mapY):
            for x in range(self.mapX):
                if self.map[y * self.mapX + x] > 0:
                    color = WHITE
                else:
                    color = BLACK
                xo = x*self.mapS
                yo = x*self.mapS
                pygame.draw.rect(self.screen, color, pygame.Rect(xo + 1, yo + 1, xo + self.mapS - 1, yo + self.mapS - 1))
                pygame.display.flip()


def main():
    raycaster = Raycaster()
    raycaster.run()

if __name__ == '__main__':
    main()