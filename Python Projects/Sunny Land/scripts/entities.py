import math
import random

import pygame

class PhysicsEntity:
    def __init__(self, game, e_type, position, size):
        self.game = game
        self.type = e_type
        self.pos = list(position)
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
    
    def update(self, movement=(0, 0)):
        self.collision = {'up' : False, 'down' : False, 'left' : False, 'right' : False}

        frame_movement = (movement[0] + self.velocity[0], movement[1] + self.velocity[1])

        self.pos[0] += frame_movement[0]
        self.pos[1] += frame_movement[1]

        if movement[0] > 0:
            self.flip = False
        if movement[0] < 0:
            self.flip = True

        self.last_movement = movement
        
        self.animation.update()
    
    def render(self, surf):
        surf.blit(pygame.transform.flip(self.animation.img(), self.flip, False), (self.pos[0] + self.anim_offset[0], self.pos[1] + self.anim_offset[1]))

class Player(PhysicsEntity):
    def __init__(self, game, pos, size):
        super().__init__(game, 'player', pos, size)
        self.jumps = 1
    
    def update(self, movement=(0, 0)):
        super().update(movement)

        if movement[0] != 0:
            self.set_action('run')
        else:
            self.set_action('idle')

    def render(self, surf):
        super().render(surf)

    def jump(self):
        if self.jumps:
            self.velocity[1] = -3
            self.jumps -= 1
            return True        
