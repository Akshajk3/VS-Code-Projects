import struct
from pygame.math import Vector2 as vec2

class WADReader():
    def __init__(self, wad_path):
        self.wad_file = open(wad_path, 'rb')
        self.header = self.read_header()
        self.directory = self.read_directory()

    def read_vertex(self, offset):
        # 4 bytes = 2h + 2h
        x = self.read_2_bytes(offset=offset, byte_format='h')
        y = self.read_2_bytes(offset=offset + 2, byte_format='h')
        return vec2(x, y)

    def read_directory(self):
        directory = []
        for i in range(self.header['lump_count']):
            offset = self.header['init_offset'] + i * 16
            lump_info = {
                'lump_offset' : self.read_4_bytes(offset),
                'lump_size' : self.read_4_bytes(offset + 4),
                'lump_name' : self.read_string(offset + 8, num_bytes=8)
            }
            directory.append(lump_info)
        return directory

    def read_header(self):
        return {
            'wad_type' : self.read_string(offset=0, num_bytes=4),
            'lump_count' : self.read_4_bytes(offset=4),
            'init_offset' : self.read_4_bytes(offset=8)
        }
    
    def read_1_byte(self, offset, byte_format):
        # B - unsigned char, b - signed char
        return self.read_bytes(offset=offset, num_bytes=1, byte_format=byte_format)[0]

    def read_2_bytes(self, offset, byte_format):
        # H - uint16 - int16
        return self.read_bytes(offset=offset, num_bytes=2, byte_format=byte_format)[0]

    def read_4_bytes(self, offset, byte_format='i'):
        # I = uint32, i - int32
        return self.read_bytes(offset=offset, num_bytes=4, byte_format=byte_format)[0]

    def read_string(self, offset, num_bytes):
        # c = char
        return ''.join(b.decode('ascii') for b in self.read_bytes(offset, num_bytes, byte_format='c' * num_bytes)
                       if ord(b) != 0).upper()

    def read_bytes(self, offset, num_bytes, byte_format):
        self.wad_file.seek(offset)
        buffer = self.wad_file.read(num_bytes)
        return struct.unpack(byte_format, buffer)

    def close(self):
        self.wad_file.close()