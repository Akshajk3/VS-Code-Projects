import struct

class WADReader:
    def __init__(self, wad_path):
        self.wad_file = open(wad_path, 'rb')
        self.header = self.read_header()
        print('\n', self.header)

    def read_header(self):
        return {
            'wad_type' : self.read_string(offset=0, num_bytes=4),
            'lump_count' : self.read_4_bytes(offset=4),
            'init_offset' : self.read_4_bytes(offset = 8)
        }

    def read_4_bytes(self, offset, byte_format='i'):
        return self.read_bytes(offset, 4, byte_format)[0]

    def read_string(self, offset, num_bytes):
        return ''.join(b.decode('ascii') for b in self.read_bytes(offset, num_bytes, byte_format='c' * num_bytes)
                       if ord(b) != 0).upper() 

    def close(self):
        self.wad_file.close()

    def read_bytes(self, offset, num_bytes, byte_format):
        self.wad_file.seek(offset)
        buffer = self.wad_file.read(num_bytes)
        return struct.unpack(byte_format, buffer)