import pygame

class Entity:
    def __init__(self, game, e_type, position, size):
        self.game = game
        self.type = e_type
        self.pos = position
        self.size = size
        self.collisions = {"up" : False, "down" : False, "left" : False, "right" : False}

        self.action = ""
        
        self.last_movement = [0, 0]

    def rect(self):
        return pygame.Rect(self.pos[0], self.pos[1], self.size[0], self.size[1])
    
    def set_action(self, action):
        if action != self.action:
            self.action = action
            self.animation = self.game.assets[self.type + '/' + self.action].copy()
    
    def update(self, tilemap, movement=(0, 0)):
        self.collisions = {"up" : False, "down" : False, "left" : False, "right" : False}

        frame_movement = (movement[0], movement[1])

        self.pos[0] += frame_movement[0]
        self.pos[1] += frame_movement[1]