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
    
    def update(self, tilemap, movement=(0, 0)):
        self.collision = {'up' : False, 'down' : False, 'left' : False, 'right' : False}

        frame_movement = (movement[0] + self.velocity[0], movement[1] + self.velocity[1])

        self.pos[0] += frame_movement[0]
        entiy_rect = self.rect()
        for rect in tilemap.physics_rects_around(self.pos):
            if entiy_rect.colliderect(rect):
                if frame_movement[0] > 0:
                    entiy_rect.right = rect.left
                    self.collision['right'] = True
                if frame_movement[0] < 0:
                    entiy_rect.left = rect.right
                    self.collision['left'] = True
        self.pos[1] += frame_movement[1]
        entiy_rect = self.rect()
        for rect in tilemap.physics_rects_around(self.pos):
            if entiy_rect.colliderect(rect):
                if frame_movement[1] > 0:
                    entiy_rect.bottom = rect.top
                    self.collision['down'] = True
                if frame_movement[1] < 0:
                    entiy_rect.top = rect.bottom
                    self.collision['up'] = True

        if movement[0] > 0:
            self.flip = False
        if movement[0] < 0:
            self.flip = True

        self.last_movement = movement
    
        self.velocity[1] = min(5, self.velocity[1] + 0.1)

        if self.collision['down'] or self.collision['up']:
            self.velocity[1] = 0
        
        self.animation.update()
    
    def render(self, surf):
        surf.blit(pygame.transform.flip(self.animation.img(), self.flip, False), (self.pos[0] + self.anim_offset[0], self.pos[1] + self.anim_offset[1]))

class Player(PhysicsEntity):
    def __init__(self, game, pos, size):
        super().__init__(game, 'player', pos, size)
        self.air_time = 0
        self.jumps = 1
    
    def update(self, tilemap, movement=(0, 0)):
        super().update(tilemap, movement)

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
