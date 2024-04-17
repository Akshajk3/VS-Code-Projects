from settings import *
import moderngl as mgl
import pygame
import sys
from shader_program import ShaderProgram
from scene import Scene
from player import Player

class VoxelEngine:
    def __init__(self):
        pygame.init()
        pygame.display.gl_set_attribute(pygame.GL_CONTEXT_MAJOR_VERSION, 3)
        pygame.display.gl_set_attribute(pygame.GL_CONTEXT_MINOR_VERSION, 3)
        pygame.display.gl_set_attribute(pygame.GL_CONTEXT_PROFILE_MASK, pygame.GL_CONTEXT_PROFILE_CORE)
        pygame.display.gl_set_attribute(pygame.GL_DEPTH_SIZE, 24)

        pygame.display.set_mode(WIN_RES, flags=pygame.OPENGL | pygame.DOUBLEBUF)
        self.ctx = mgl.create_context()

        self.ctx.enable(flags=mgl.DEPTH_TEST | mgl.BLEND)
        self.ctx.gc_mode = 'auto'

        self.clock = pygame.time.Clock()
        self.delta_time = 0
        self.time = 0

        pygame.event.set_grab(True)
        pygame.mouse.set_visible(False)

        self.is_running = True
        self.on_init()

    def on_init(self):
        self.player = Player(self)
        self.shader_program = ShaderProgram(self)
        self.scene = Scene(self)

    def update(self):
        pygame.mouse.set_pos((WIN_RES.x / 2, WIN_RES.y / 2))
        self.player.update()
        self.shader_program.update()
        self.scene.update()

        self.delta_time = self.clock.tick()
        self.time = pygame.time.get_ticks()
        pygame.display.set_caption(f'{self.clock.get_fps() : .0f}')

    def render(self):
        self.ctx.clear(color=BG_COLOR)
        self.scene.render()
        pygame.display.flip()

    def handle_event(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT or (event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE):
                self.is_running = False

    def run(self):
        while self.is_running:
            self.handle_event()
            self.update()
            self.render()
        pygame.quit()
        sys.exit()

if __name__ == '__main__':
    app = VoxelEngine()
    app.run()