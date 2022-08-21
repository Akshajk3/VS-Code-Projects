import pygame
import random
import numpy as np

pygame.init()

font = pygame.font.SysFont('arial', 25)

SCREEN_WIDTH = 858
SCREEN_HEIGHT = 525

DISPLAY = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Pong")

PADDLE_WIDHT = 20
PADDLE_HEIGHT = 200

BALL_SIZE = 20

Y_DELTA = 50

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

class LeftPaddle:
    
    def __init__(self):
        self.velocity = 50
        self.x_pos = 50
        self.y_pos = 100
        self.clock = pygame.time.Clock()


    def move(self):
        edge_up = self.y_pos <= 0
        edge_down = self.y_pos >= 325

        

        user_input = pygame.key.get_pressed()
        
        if user_input[pygame.K_UP] and edge_up == False:
            Y_DELTA = -0.05
        elif user_input[pygame.K_DOWN] and edge_down == False:
            Y_DELTA = 0.05
        else:
            Y_DELTA = 0

        self.y_pos += Y_DELTA
            

        
    
    def draw(self):

        pygame.draw.rect(DISPLAY, WHITE, pygame.Rect(self.x_pos, self.y_pos, PADDLE_WIDHT, PADDLE_HEIGHT))

        text = font.render("Score", True, WHITE)
        DISPLAY.blit(text, [SCREEN_WIDTH/2 - 50, 0])

class RightPaddle:
    
    def __init__(self):
        self.velocity = 50
        self.x_pos = 808
        self.y_pos = 100
        self.clock = pygame.time.Clock
    
    def move(self):
        edge_up = self.y_pos <= 0
        edge_down = self.y_pos >= 325

        user_input = pygame.key.get_pressed()

        if user_input[pygame.K_UP] and edge_up == False:
            Y_DELTA = -0.05
        elif user_input[pygame.K_DOWN] and edge_down == False:
            Y_DELTA = 0.05
        else:
            Y_DELTA = 0
        
        self.y_pos += Y_DELTA
    
    def draw(self):

        pygame.draw.rect(DISPLAY, WHITE, pygame.Rect(self.x_pos, self.y_pos, PADDLE_WIDHT, PADDLE_HEIGHT))

class Ball:

    def __init__(self):
        self.x_delta = 0
        self.y_delta = 0.05
        self.x_pos = SCREEN_WIDTH/2
        self.y_pos = SCREEN_HEIGHT/2
        self.clock = pygame.time.Clock()
    
    def bounce(self):
        leftPaddle = LeftPaddle()
        rightPaddle = RightPaddle()
        top_edge = self.y_pos <= 0
        bottom_edge = self.y_pos >= 505

        rect1 = pygame.Rect(DISPLAY.get_rect().center, 0, 0).inflate(75, 75)
        rect2 = pygame.Rect()

        if top_edge or bottom_edge:
            self.y_delta *= -1
        
        self.x_pos += self.x_delta
        self.y_pos += self.y_delta

    def draw(self):

        pygame.draw.rect(DISPLAY, WHITE, pygame.Rect(self.x_pos, self.y_pos, BALL_SIZE, BALL_SIZE))



if __name__ == '__main__':
    run = True
    leftPaddle = LeftPaddle()
    rightPaddle = RightPaddle()
    ball = Ball()
    while run:
        DISPLAY.fill(BLACK)
        leftPaddle.draw()
        rightPaddle.draw()
        ball.draw()
        leftPaddle.move()
        rightPaddle.move()
        ball.bounce()
        pygame.display.flip()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
    