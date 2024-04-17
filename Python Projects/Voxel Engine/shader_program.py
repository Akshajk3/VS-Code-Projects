from settings import *

class ShaderProgram:
    def __init__(self, app):
        self.app = app
        self.ctx = app.ctx
        self.player = app.player
        self.chunk = self.get_program('chunk')
        self.set_uniform_on_init()

    def set_uniform_on_init(self):
        self.chunk['m_proj'].write(self.player.m_proj)
        self.chunk['m_model'].write(glm.mat4())

    def update(self):
        self.chunk['m_view'].write(self.player.m_view)
    
    def get_program(self, shader_name):
        with open(f'shaders/{shader_name}.vert') as file:
            vertex_shader = file.read()

        with open(f'shaders/{shader_name}.frag') as file:
            fragment_shader = file.read()

        program = self.ctx.program(vertex_shader=vertex_shader, fragment_shader=fragment_shader)
        return program