import pygame
import sys

WIN_RES = (400, 600)
BLOCK_SIZE = 20

O = [0, 0, 0, 0, 0,
      0, 1, 1, 0, 0,
      0, 1, 1, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,]

I = [0, 0, 0, 0, 0,
     0, 0, 1, 0, 0,
     0, 0, 1, 0, 0,
     0, 0, 1, 0, 0,
     0, 0, 1, 0, 0,]

S = [[0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 1, 1, 0,
      0, 1, 1, 0, 0,
      0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0,
      0, 0, 1, 0, 0,
      0, 0, 1, 1, 0,
      0, 0, 0, 1, 0,
      0, 0, 0, 0, 0,]]

class Tetris:
    def __init__(self):
        self.screen = pygame.display.set_mode(WIN_RES)
        self.clock = pygame.time.Clock()
        self.running = True
        self.dt = 1 / 60

    def update(self):
        pygame.display.set_caption("Vetris")

    def draw(self):
        self.screen.fill((77, 77, 77))
        self.draw_overlay()
        pygame.display.flip()

    def draw_overlay(self):
        pygame.draw.line(self.screen, (255, 255, 255), (0, 0), (0, 600), 10)
        pygame.draw.line(self.screen, (255, 255, 255), (400, 0), (400, 600), 10)
        pygame.draw.line(self.screen, (255, 255, 255), (0, 0), (400, 0), 10)
        pygame.draw.line(self.screen, (255, 255, 255), (0, 600), (400, 600), 10)
        pygame.draw.rect(self.screen, (255, 255, 255), pygame.Rect(100, 100, BLOCK_SIZE, BLOCK_SIZE))
    
    def check_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.running = False
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    self.running = False

    def draw_tetriminos(self):
        pass

    def run(self):
        while self.running:
            self.check_events()
            self.update()
            self.draw()
        pygame.quit()
        sys.exit()
        

if __name__ == '__main__':
    tetris = Tetris()
    tetris.run()