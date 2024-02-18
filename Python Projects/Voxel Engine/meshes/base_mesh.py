import numpy

class BaseMesh:
    def __init__(self):
        self.ctx = None
        self.program = None
        self.vbo_format = None
        self.attrs: tuple[str, ...] = None
        self.vao = None

    def get_vertex_data(self) -> numpy.array: ...

    def get_vao(self):
        vertex_data = self.get_vertex_data()
        vbo = self.ctx.buffer(vertex_data)
        vao = self.ctx.vertex_array(
            self.program, [(vbo, self.vbo_format, *self.attrs)], skip_erors=True
        )
        return vao

    def render(self):
        pass