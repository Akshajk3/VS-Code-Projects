from settings import *
from pygame.math import Vector2 as vec2
import pygame

class Player:
    def __init__(self, engine):
        self.engine = engine
        self.thing = engine.wad_data.things[0]
        self.pos = self.thing.pos
        self.angle = self.thing.angle

    def update(self):
        self.control()

    def control(self):
        speed = PLAYER_SPEED * self.engine.dt
        rot_speed = PLAYER_ROT_SPEED * self.engine.dt

        key_state = pygame.key.get_pressed()
        if key_state[pygame.K_LEFT]:
            self.angle += rot_speed
        if key_state[pygame.K_RIGHT]:
            self.angle -= rot_speed

        inc = vec2(0)
        if key_state[pygame.K_a]:
            inc += vec2(0, speed).rotate(self.angle)
        if key_state[pygame.K_d]:
            inc += vec2(0, -speed).rotate(self.angle)