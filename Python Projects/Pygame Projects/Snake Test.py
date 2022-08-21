from tarfile import BLOCKSIZE
import pygame
import random
from enum import Enum
from collections import namedtuple
import numpy as np

pygame.init()
font = pygame.font.SysFont('arial', 25)

class Direction(Enum):
    RIGHT = 1
    LEFT = 2
    UP = 3
    DOWN = 4

Point = namedtuple('Point', 'x, y')

WHITE = (255, 255, 255)
RED = (200, 0, 0)
BLUE1 = (0, 0, 255)
BLUE2 = (0, 100, 255)
BLACK = (0, 0, 0)

BLOCKSIZE = 20
SPEED = 40

class SnakeGame:

    def __init__(self, w=480, h=640):
        self.w = w
        self.h = h

        self.display = pygame.display.set_mode(self.w, self.h)
        pygame.display.set_caption('Snake Game')
        self.clock = pygame.time.Clock()
        
        self.direction = Direction.RIGHT

        self.head = Point(self.w/2, self.h/2)

