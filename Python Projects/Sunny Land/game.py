import sys

import pygame

from scripts.utils import load_image, load_images, Animation
from scripts.entities import PhysicsEntity, Player
from scripts.tilemap import Tilemap

class Game:
    def __init__(self):
        pygame.init()

        pygame.display.set_caption("VINDEL")
        self.screen = pygame.display.set_mode((640, 480))

        self.display = pygame.Surface((320, 240))

        self.clock = pygame.time.Clock()
        
        self.movement = [False, False]

        self.assets = {
            'grass' : load_images('grass'),
            'player/idle' : Animation(load_images('entities/player/idle'), img_dur=8),
            'player/run' : Animation(load_images('entities/player/walk'), img_dur=6),
            'player/jump' : Animation(load_images('entities/player/fall')),
            'player/attack' : Animation(load_images('entities/player/attack1'))
        }

        self.background = load_image('background.png')
        self.background = pygame.transform.scale(self.background, (640, 480))

        self.player = Player(self, (50, 50), (8, 12))

        self.tilemap = Tilemap(self, tile_size=16)

    def run(self):
        while True:
            self.display.fill((0, 0, 0))
            self.display.blit(self.background,  (0, 0))

            self.player.update(self.tilemap, (self.movement[1] - self.movement[0], 0))
            self.player.render(self.display)

            self.tilemap.render(self.display)

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_LEFT:
                        self.movement[0] = True
                    if event.key == pygame.K_RIGHT:
                        self.movement[1] = True
                    if event.key == pygame.K_UP:
                        self.player.jump()
                if event.type == pygame.KEYUP:
                    if event.key == pygame.K_LEFT:
                        self.movement[0] = False
                    if event.key == pygame.K_RIGHT:
                        self.movement[1] = False

            self.screen.blit(pygame.transform.scale(self.display, self.screen.get_size()), (0, 0))
            pygame.display.update()
            self.clock.tick(60)

Game().run()