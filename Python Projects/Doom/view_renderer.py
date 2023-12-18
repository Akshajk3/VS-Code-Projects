from settings import *
import random
from random import randrange as rnd
import pygame.gfxdraw as gfx

class ViewRenderer:
    def __init__(self, engine):
        self.screen = engine.screen
        self.colors = {}

    def get_color(self):
        rng = 50, 256
        return rnd(*rng), rnd(*rng), rnd(*rng)

    def draw_vline(self, x, y1, y2):
        gfx.vline(self.screen, x, y1, y2, self.get_color())