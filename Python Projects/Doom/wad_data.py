from wad_reader import WADReader

class WADData:
    LUMP_INDICES = {
        'THINGS' : 1, 'LINEDEFS' : 2, 'SIDEDEFS' : 3, 'VERTEXES' : 4, 'SEGS' : 5,
        'SSECTORS' : 6, 'NODES' : 7, 'SECTORS' : 8, 'REJECTS' : 9, 'BLOCKMAP' : 10
    }

    def __init__(self, engine, map_name):
        self.reader = WADReader(engine.wad_path)
        self.map_index = self.get_lump_index(lump_name=map_name)
        print(f'\n{map_name}_index = {self.map_index}')

        self.reader.close()

    def get_lump_data(self, reader_func, lump_index, num_bytes, header_length = 0):
        lump_info = self.reader.directroy[lump_index]
        count = lump_info['lump_size'] // num_bytes
        data = []
        for i in range(count):
            offset = lump_info['lump_offset'] + i * num_bytes + header_length
            data.append(reader_func(offset))
        return data


    def get_lump_index(self, lump_name):
        for index, lump_info in enumerate(self.reader.directroy):
            if lump_name in lump_info.values():
                return index