import math
import random
import sys
import os

import neat
import pygame

WIDTH = 1600
HEIGHT = 880

CAR_SIZE_X = 60
CAR_SIZE_Y = 60

RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)

class Car:
    def __init__(self):
        self.sprite = pygame.image.load('car.png').convert()
        self.sprite = pygame.transform.scale(self.sprite, (CAR_SIZE_X, CAR_SIZE_Y))
        self.rotated_sprite = self.sprite

        self.position = [830, 920]
        self.angle = 0
        self.speed = 0

        self.speed_set = False

        self.center = [self.position[0] + CAR_SIZE_X / 2, self.position[1] + CAR_SIZE_Y / 2]

        self.radars = []
        self.drawing_radars = []

        self.alive = True

        self.distance = 0
        self.time = 0

    def draw(self, screen):
        screen.blit(self.rotated_sprite, self.position)
    
    def draw_radars(self, screen):
        for radar in self.radars:
            position = radar[0]
            pygame.draw.line(screen, GREEN, self.center, position)
            pygame.draw.circle(screen, RED, position, 5)
    
    def update(self, game_map):
        pass