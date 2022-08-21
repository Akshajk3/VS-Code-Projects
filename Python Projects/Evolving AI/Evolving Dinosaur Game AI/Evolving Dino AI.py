import pygame
import os
import random
import sys
import neat
import math

pygame.init()

SCREEN_HIEGHT = 600
SCREEN_WIDTH = 1100
SCREEN = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HIEGHT))
pygame.display.set_caption("Dino Game AI")

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
        self.color = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
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
        pygame.draw.rect(SCREEN, self.color, (self.rect.x, self.rect.y, self.rect.width, self.rect.height), 2)
        for obstacle in obstacles:
            pygame.draw.line(SCREEN, self.color, (self.rect.x + 54, self.rect.y + 12), obstacle.rect.center, 2)

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
    dino.pop(index)
    ge.pop(index)
    nets.pop(index)

def distance(pos_a, pos_b):
    dx = pos_a[0] - pos_b[0]
    dy = pos_a[1] - pos_b[1]
    return math.sqrt(dx**2 + dy**2)


def eval_genomes(genomes, config):
    global game_speed, x_pos_bg, y_pos_bg, points, obstacles, ge, nets, dino, points
    clock = pygame.time.Clock()
    points = 0

    obstacles = []
    dino = []
    ge = []
    nets = []

    for genome_id, genome in genomes:
        dino.append(Dino())
        ge.append(genome)
        net = neat.nn.FeedForwardNetwork.create(genome, config)
        nets.append(net)
        genome.fitness = 0


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
    
    def statistics():
        global dino, game_speed, ge
        text_1 = FONT.render(f'Dinosaurs Alive: {str(len(dino))}', True, (0, 0, 0))
        text_2 = FONT.render(f'Generation: {pop.generation+1}', True, (0, 0, 0))
        text_3 = FONT.render(f'Game Speed: {str(game_speed)}', True, (0, 0, 0))

        SCREEN.blit(text_1, (50, 450))
        SCREEN.blit(text_2, (50, 480))
        SCREEN.blit(text_3, (50, 510))

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

        for dinosaur in dino:
            dinosaur.update()
            dinosaur.draw(SCREEN)

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
            for i, dinosaur in enumerate(dino):
                if dinosaur.rect.colliderect(obstacle.rect):
                    ge[i].fitness += points
                    remove(i)


        for i, dinosaur in enumerate(dino):
            output = nets[i].activate((dinosaur.rect.y,
                                       distance((dinosaur.rect.x, dinosaur.rect.y),
                                        obstacle.rect.midtop)))
                                        
            if output[0] > 0.5 and dinosaur.rect.y == dinosaur.Y_POS:
                dinosaur.dino_jump = True
                dinosaur.dino_run = False
        statistics()
        score()
        background()
        clock.tick(30)
        pygame.display.update()


def run(config_path):
    global pop
    config = neat.config.Config(
        neat.DefaultGenome,
        neat.DefaultReproduction,
        neat.DefaultSpeciesSet,
        neat.DefaultStagnation,
        config_path
    )

    pop = neat.Population(config)
    pop.run(eval_genomes, 50)

if __name__ == '__main__':
    local_dir = os.path.dirname(__file__)
    config_path = os.path.join(local_dir, 'config.txt')
    run(config_path)