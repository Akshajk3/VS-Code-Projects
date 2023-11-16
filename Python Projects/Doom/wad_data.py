from wad_reader import WADReader

class WADData:
    LUMP_INDICES = {
        'THINGS' : 1, 'LINEDEFS' : 2, 'SIDEDEFS' : 3, 'VERTEXES' : 4, 'SEGS' : 5,
        'SSECTORS' : 6, 'NODES' : 7, 'SECTOR' : 8, 'REJECT' : 9, 'BLOCKMAP' : 10
    }

    def __init__(self, engine, map_name):
        self.reader = WADReader(engine.wad_path)
        self.map_index = self.get_lump_index(lump_name=map_name)

        self.reader.close()

    def get_lump_data():
        pass
    
    def get_lump_index(self, lump_name):
        for index, lump_info in enumerate(self.reader.directory):
            if lump_name in lump_info.values():
                return index