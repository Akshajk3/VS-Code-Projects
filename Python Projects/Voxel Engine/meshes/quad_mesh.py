from settings import *
from meshes.base_mesh import BaseMesh

class QuadMesh(BaseMesh):
    def __init__(self, app):
        super().__init__()

        self.app = app