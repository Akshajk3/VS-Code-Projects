import pygame

pygame.init()


SCREEN = pygame.display.set_mode((800, 800))
pygame.display.set_caption("Testing")

RED = (255, 0, 0)
WHITE = (255, 255, 255)

def main():
    run = True
    COLOR = WHITE
    rect = pygame.Rect(30, 30, 50, 50)
    touching = False

    while run:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

            if rect.collidepoint(pygame.mouse.get_pos()):
                COLOR = RED
                touching = True
            else:
                COLOR = WHITE

            if event.type == pygame.MOUSEBUTTONDOWN and touching:
                pygame.quit()
                quit()
        
        pygame.draw.rect(SCREEN, COLOR, rect)
        pygame.display.update()

        

main()