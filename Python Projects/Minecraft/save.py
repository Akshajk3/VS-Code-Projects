import nbtlib as nbt
import base36
import chunks

class Save:
    def __init__(self, world, path = "save"):
        self.world = world
        self.path = path

    def chunk_position_to_path(self, chunk_position):
        x, y, z = chunk_position

        chunk_path = '/'.join((self.path,
            base36.dumps(x % 64), base36.dumps(z % 64),
            f"c.{base36.dumps(x)}.{base36.dumps(z)}.dat"))
        
        return chunk_path
    
    def load_chunk(self, chunk_position):
        # load the chunk file
        
        chunk_path = self.chunk_position_to_path(chunk_position)

        try:
            chunk_blocks = nbt.load(chunk_path)["Level"]["Blocks"]
        
        except FileNotFoundError:
            return

        # create chunk and fill it with the blocks from our chunk file

        self.world.chunks[chunk_position] = chunks.Chunk(self.world, chunk_position)

        for x in range(chunks.CHUNK_WIDTH):
            for y in range(chunks.CHUNK_HEIGHT):
                for z in range(chunks.CHUNK_LENGTH):
                    self.world.chunks[chunk_position].blocks[x][y][z] = chunk_blocks[
                        x * chunks.CHUNK_LENGTH * chunks.CHUNK_HEIGHT +
                        z * chunks.CHUNK_HEIGHT +
                        y]

    def load(self):
        for x in range(-4, 4):
            for y in range(-4, 4):
                self.load_chunk((x, 0, y))