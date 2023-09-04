import pygame
import moderngl as mgl
import sys

class GraphicsEngine:
    def __init__(self, win_size=(1280, 720)):
        pygame.init()

        self.WIN_SIZE = win_size
        pygame.display.gl_set_attribute(pygame.GL_CONTEXT_MAJOR_VERSION, 3)
        pygame.display.gl_set_attribute(pygame.GL_CONTEXT_MINOR_VERSION, 3)
        pygame.display.gl_set_attribute(pygame.GL_CONTEXT_PROFILE_MASK, pygame.GL_CONTEXT_PROFILE_CORE)

        pygame.display.set_mode(self.WIN_SIZE, flags=pygame.OPENGL | pygame.DOUBLEBUF)

        self.ctx = mgl.create_context()
        self.clock = pygame.time.Clock()

    def check_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
    
    def render(self):
        self.ctx.clear(color=(0.08, 0.16, 0.18, 1))

        pygame.display.flip()
    
    def run(self):
        while True:
            self.check_events()
            self.render()
            self.clock.tick(60)

if __name__ == '__main__':
    app = GraphicsEngine()
    app.run()