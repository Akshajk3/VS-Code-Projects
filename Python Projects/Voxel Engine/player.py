import pygame
from camera import Camera
from settings import *

class Player(Camera):
    def __init__(self, app, position = PLAYER_POS, yaw = -90, pitch = 0):
        self.app = app
        super().__init__(position, yaw, pitch)
    
    def update(self):
        self.keyboard_control()
        self.mouse_control()
        super().update()

    def mouse_control(self):
        mouse_dx, mouse_dy = pygame.mouse.get_rel()
        if mouse_dx:
            self.rotate_yaw(mouse_dx * MOUSE_SENSITIVITY)
        if mouse_dy:
            self.rotate_pitch(mouse_dy * MOUSE_SENSITIVITY)

    def keyboard_control(self):
        key_state = pygame.key.get_pressed()
        vel = PLAYER_SPEED * self.app.delta_time
        if key_state[pygame.K_w]:
            self.move_forward(vel)
        if key_state[pygame.K_s]:
            self.move_backward(vel)
        if key_state[pygame.K_d]:
            self.move_right(vel)
        if key_state[pygame.K_a]:
            self.move_left(vel)
        if key_state[pygame.K_SPACE]:
            self.move_up(vel)
        if key_state[pygame.K_LSHIFT]:
            self.move_down(vel)