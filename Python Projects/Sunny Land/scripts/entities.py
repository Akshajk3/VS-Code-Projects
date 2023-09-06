import math
import random

import pygame

class PhysicsEntity:
    def __init__(self, game, e_type, position, size):
        self.game = game
        self.type = e_type
        self.pos = position
        self.size = size
        self.velocity = [0, 0]
        self.collision = {'up' : False, 'down' : False, 'left' : False, 'right' : False}

        self.action = ' '
        self.anim_offset = (-3, -3)
        self.flip = False
        self.set_action('idle')

        self.last_movement = [0, 0]
    
    def rect(self):
        return pygame.Rect(self.pos[0], self.pos[1], self.size[0], self.size[1])
    
    def set_action(self, action):
        if action != self.action:
            self.action = action
            self.animation = self.game.assets[self.type + '/' + self.action].copy()
    
    def update(self, tilemap, movement=(0, 0)):
        self.collision = {'up' : False, 'down' : False, 'left' : False, 'right' : False}

        frame_movement = (movement[0])