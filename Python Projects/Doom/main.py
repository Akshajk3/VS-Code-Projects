from wad_data import WADData
from settings import *
import pygame
import sys
from map_renderer import MapRenderer
from player import Player
from bsp import BSP

class DoomEngine:
    def __init__(self, wad_path = 'wad/DOOM1.WAD'):
        self.wad_path = wad_path
        self.screen = pygame.display.set_mode(WIN_RES)
        self.clock = pygame.time.Clock()
        self.running = True
        self.dt = 1 / 60
        self.on_init()
    
    def on_init(self):
        self.wad_data = WADData(self, 'E1M1')
        self.map_renderer = MapRenderer(self)
        self.player = Player(self)
        self.bsp = BSP(self)

    def update(self):
        self.player.update()
        self.bsp.update()
        self.dt = self.clock.tick()
        pygame.display.set_caption(f'{self.clock.get_fps()}')


    def draw(self):
        pygame.display.flip()
        self.screen.fill('black')
        self.map_renderer.draw()

    def check_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.running = False

    def run(self):
        while self.running:
            self.check_events()
            self.update()
            self.draw()
        pygame.quit()
        sys.exit()

if __name__ == '__main__':
    doom = DoomEngine()
    doom.run()