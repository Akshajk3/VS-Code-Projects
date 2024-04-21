import pygame
import moderngl as mgl

class Textures:
    def __init__(self, app):
        self.app = app
        self.ctx = app.ctx

        self.texture_0 = self.load('frame.png')

        self.texture_0.use(location=0)

    def load(self, filename):
        texture = pygame.image.load(f'assets/{filename}')
        texture = pygame.transform.flip(texture, flip_x=True, flip_y=False)

        texture = self.ctx.texture(
            size = texture.get_size(),
            components = 4,
            data = pygame.image.tostring(texture, 'RGBA', False)
        )
        texture.anisotropy = 32.0
        texture.build_mipmaps()
        texture.filter = (mgl.NEAREST, mgl.NEAREST)
        return texture

