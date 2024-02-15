from settings import *


class BSP:
    def __init__(self, engine):
        self.engine = engine
        self.player = engine.player
        self.nodes = engine.wad_data.sub_sectors
        self.segs = engine.wad_data.segments
        self.rood_node_id = len(self.nodes)

    def update(self):
        pass
