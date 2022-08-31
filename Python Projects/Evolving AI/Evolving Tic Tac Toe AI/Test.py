import pygame
from pygame.locals import *
import sys
 
pygame.init()
display = pygame.display.set_mode((300, 300))
FPS_CLOCK = pygame.time.Clock()


class Player:
    def __init__(self):
        self.rect = pygame.draw.rect(display, (255, 0, 0), (100, 100, 100, 100))
    
    def draw(self):
        self.rect
 
player = Player()
 
while 1:

    player.draw()

    for event in pygame.event.get():
        ...
        ...
        if event.type == pygame.MOUSEBUTTONDOWN:           
            if player.rect.collidepoint(pygame.mouse.get_pos()):
                print("Mouse clicked on the Player")
  
        if event.type == pygame.MOUSEBUTTONUP:
            if player.rect.collidepoint(pygame.mouse.get_pos()):
                print("Mouse released on the Player")
        
        if event.type == pygame.QUIT:
            pygame.quit()