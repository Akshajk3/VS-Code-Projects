import pygame
import os
import random
import sys

pygame.init()

SCREEN_HIEGHT = 600
SCREEN_WIDTH = 1100
SCREEN = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HIEGHT))
pygame.display.set_caption("Playable Dino Game")

RUNNING = [pygame.image.load(os.path.join("DinoRun1.png")), pygame.image.load(os.path.join("DinoRun2.png"))]
JUMPING = pygame.image.load(os.path.join("DinoJump.png"))

SMALL_CACTI = [pygame.image.load(os.path.join("SmallCactus1.png")), pygame.image.load(os.path.join("SmallCactus2.png")), pygame.image.load(os.path.join("SmallCactus3.png"))]
LARGE_CACTI = [pygame.image.load(os.path.join("LargeCactus1.png")), pygame.image.load(os.path.join("LargeCactus2.png")), pygame.image.load(os.path.join("LargeCactus3.png"))]

BG = pygame.image.load(os.path.join("Track.png"))

FONT = pygame.font.Font('freesansbold.ttf', 20)


class Dino:
    X_POS = 80
    Y_POS = 310
    JUMP_VEL = 8.5

    def __init__(self, img=RUNNING[0]):
        self.image = img
        self.dino_run = True
        self.dino_jump = False
        self.jump_vel = self.JUMP_VEL
        self.rect = pygame.Rect(self.X_POS, self.Y_POS, img.get_width(), img.get_height())
        self.step_index = 0

    def update(self):
        if self.dino_run:
            self.run()
        if self.dino_jump:
            self.jump()
        if self.step_index >= 10:
            self.step_index = 0

    def run(self):
        self.image = RUNNING[self.step_index // 5]
        self.rect.x = self.X_POS
        self.rect.y = self.Y_POS
        self.step_index += 1

    def jump(self):
        self.image = JUMPING
        if self.dino_jump:
            self.rect.y -= self.jump_vel * 4
            self.jump_vel -= 0.8
        if self.jump_vel <= -self.JUMP_VEL:
            self.dino_jump = False
            self.dino_run = True
            self.jump_vel = self.JUMP_VEL

    def draw(self, SCREEN):
        SCREEN.blit(self.image, (self.rect.x, self.rect.y))

class Obstacle:
    def __init__(self, image, number_of_cacti):
        self.image = image
        self.type = number_of_cacti
        self.rect = self.image[self.type].get_rect()
        self.rect.x = SCREEN_WIDTH

    def update(self):
        self.rect.x -= game_speed
        if self.rect.x < -self.rect.width:
            obstacles.pop()

class SmallCactus(Obstacle):
    def __init__(self, image, number_of_cacti):
        super().__init__(image, number_of_cacti)
        self.rect.y = 325
        
    def draw(self, SCREEN):
        SCREEN.blit(self.image[self.type], self.rect)

class LargeCactus(Obstacle):
    def __init__(self, image, number_of_cacti):
        super().__init__(image, number_of_cacti)
        self.rect.y = 300
    
    def draw(self, SCREEN):
        SCREEN.blit(self.image[self.type], self.rect)

def remove(index):
    dino.pop()

def main():
    global game_speed, x_pos_bg, y_pos_bg, points, obstacles, dino, points
    clock = pygame.time.Clock()
    points = 0

    obstacles = []
    dino = [Dino()]

    x_pos_bg = 0
    y_pos_bg = 380
    game_speed = 20

    def score():
        global points, game_speed
        points += 1
        if points % 100 == 0:
            game_speed += 1
        text = FONT.render(f'points: {str(points)}', True, (0, 0, 0))
        SCREEN.blit(text, (950, 50))
    
    def background():
        global x_pos_bg, y_pos_bg
        image_width = BG.get_width()
        SCREEN.blit(BG, (x_pos_bg, y_pos_bg))
        SCREEN.blit(BG, (image_width + x_pos_bg, y_pos_bg))
        if x_pos_bg <= -image_width:
            x_pos_bg = 0
        x_pos_bg -= game_speed

    run = True

    while run:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
        SCREEN.fill((225, 225, 225))

        for dinos in dino:
            dinos.update()
            dinos.draw(SCREEN)

        if len(dino) == 0:
            break

        if len(obstacles) == 0:
            rand_int = random.randint(0, 1)
            if rand_int == 0:
                obstacles.append(SmallCactus(SMALL_CACTI, random.randint(0, 2)))
            elif rand_int == 1:
                obstacles.append(LargeCactus(LARGE_CACTI, random.randint(0, 2)))

        for obstacle in obstacles:
            obstacle.draw(SCREEN)
            obstacle.update()
            for i, dinos in enumerate(dino):
                if dinos.rect.colliderect(obstacle.rect):
                    remove(i)

        user_input = pygame.key.get_pressed()

        for i, dinos in enumerate(dino):
            if user_input[pygame.K_SPACE]:
                dinos.dino_jump = True
                dinos.dino_run = False

        score()
        background()
        clock.tick(30)
        pygame.display.update()

main()