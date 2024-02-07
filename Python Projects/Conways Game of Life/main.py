import pygame
import numpy

pygame.init()

screen_width = 800
screen_height = 600

screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("Videls Game of Life")

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

grid_width = 50
grid_height = 50

rows = screen_width // grid_width
cols = screen_height // grid_height

tiles = [[0 for _ in range(rows)] for _ in range(cols)]

def draw_grid():
        for y in range(0, screen_height, grid_height):
            pygame.draw.line(screen, WHITE, (0, y), (screen_width, y))

        for x in range(0, screen_width, grid_width):
            pygame.draw.line(screen, WHITE, (x, 0), (x, screen_height))

def place_tile(mouseX, mouseY):
    row = mouseY // grid_height
    col = mouseX // grid_width
    tiles[row][col] = 1
    print(row, col)

def main():
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                mousePos = pygame.mouse.get_pos()
                place_tile(mousePos[0], mousePos[1])
        
        screen.fill(BLACK)

        draw_grid()

        for row in range(rows):
            for col in range(cols):
                pass
                #if tiles[row][col] == 1:
                    #pygame.draw.rect(screen, WHITE, pygame.Rect(row * grid_width, col * grid_height, grid_width, grid_height))

        pygame.display.flip()

main()