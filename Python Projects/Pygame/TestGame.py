import pygame

pygame.init()

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 800

BOX_SIZE = 50

SCREEN = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Test Game")

class Player:
    def __init__(self):
        self.yVel = 0
        self.xVel = 0
        self.x_pos = SCREEN_WIDTH/2
        self.y_pos = SCREEN_HEIGHT/2
        self.rect = pygame.Rect(self.x_pos, self.y_pos, BOX_SIZE, BOX_SIZE)
        self.hSpeed = 100
        self.color = (255, 255, 255)
        self.hInput = 0

    def get_input(self):
        user_input = pygame.key.get_pressed()

        if user_input[pygame.K_LEFT] or user_input[pygame.K_a]:
            self.hInput = -1
        elif user_input[pygame.K_RIGHT] or user_input[pygame.K_d]:
            self.hInput = 1
        else:
            self.hInput = 0

        return self.hInput

    def move_player(self):
        self.xVel = self.get_input()

        self.x_pos = self.xVel

        mouseX, mouseY = pygame.mouse.get_pos()
        mouseX = mouseX - BOX_SIZE/2
        mouseY = mouseY - BOX_SIZE/2
        self.rect.x, self.rect.y = mouseX, mouseY

        print(self.rect.x)
    
    def draw(self):
        pygame.draw.rect(SCREEN, (255, 255, 255), self.rect)
        pygame.display.flip()

def update_ui():
    player = Player()

    SCREEN.fill((50, 100, 255))

    player.move_player()
    player.draw()

def get_input():
    player = Player()

    player.move_player()


def main():
    run = True
    player = Player()

    while run:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

        update_ui()
        pygame.display.update()

if __name__ == '__main__':
    main()    