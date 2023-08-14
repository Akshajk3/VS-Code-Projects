import sys

import pygame

from scripts.utils import load_image, load_images
from scripts.tilemap import Tilemap
from scripts.entities import PhysicsEntity

class Game:
    def __init__(self):
        pygame.init()

        pygame.display.set_caption("Sunny Land")
        self.screen = pygame.display.set_mode((640, 480))
        self.display = pygame.Surface((320, 240))
        
        self.clock = pygame.time.Clock()

        self.movement = [False, False]

        self.assets = {
            'grass' : load_images('tiles/grass'),
            'background' : load_image('back.png'),
            'player' : load_image('player/idle/0.png')
        }

        self.tilemap = Tilemap(self, tile_size=16)

        self.player = PhysicsEntity(self, 'player', (50, 50), (8, 15))

    def run(self):
        while True:
            self.display.blit(self.assets['background'], (0, 0))

            self.tilemap.render(self.display)

            self.player.update(self.tilemap, (self.movement[1] - self.movement[0], 0))
            self.player.render(self.display)

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()

            self.screen.blit(pygame.transform.scale(self.display, self.screen.get_size()), (0, 0))
            pygame.display.update()
            self.clock.tick(60)

Game().run()