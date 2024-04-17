from settings import *
from meshes.chunk_mesh import ChunkMesh

class Chunk:
    def __init__(self, app):
        self.app = app
        self.voxels = np.array = self.build_voxels()
        self.mesh: ChunkMesh = None
        self.build_mesh()

    def build_mesh(self):
        self.mesh = ChunkMesh(self)

    def render(self):
        self.mesh.render()

    def build_voxels(self):
        voxels = np.zeros(CHUNK_VOL, dtype='uint8')

        for x in range(CHUNK_SIZE):
            for z in range(CHUNK_SIZE):
                for y in range(CHUNK_SIZE):
                    voxels[x + CHUNK_SIZE * z + CHUNK_AREA * y] = x + y + z
        return voxels