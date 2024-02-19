# H - uint16, h - int16, I - uint32, i - int32, c - char

class Sector:
    __slots__ = [
        'floor_height',
        'ceil_height',
        'floor_texture',
        'ceil_texture',
        'light_level',
        'type',
        'tag'
    ]

class Sidedef:
    __slots__ = [
        'x_offset',
        'y_offset',
        'upper_texture',
        'lower_texture',
        'middle_texture',
        'sector_id'
    ]

    __slots__ += ['sector']

class Thing:
    __slots__ = [
        'pos',
        'angle',
        'type',
        'flags'
    ]

class Seg:
    __slots__ = [
        'start_vertex_id',
        'end_vertex_id',
        'angle',
        'linedef_id',
        'direction',
        'offset'
    ]
    __slots__ += ['start_vertex', 'end_vertex', 'linedef', 'front_sector', 'back_sector']

class SubSector:
    __slots__ = [
        'seg_count',
        'first_seg_id'
    ]

class Node:
    class BBox:
        __slots__ = ['top', 'bottom', 'left', 'right']

    __slots__ = [
        'x_partition',
        'y_partition',
        'dx_partition',
        'dy_partition',
        'bbox',
        'front_child_id',
        'back_child_id'
    ]
    def __init__(self):
        self.bbox = {'front' : self.BBox(), 'back' : self.BBox()}


class Linedef:
    __slots__ = [
        'start_vertex_id',
        'end_vertex_id',
        'flags',
        'line_type',
        'sector_tag',
        'front_sidedef_id',
        'back_sidedef_id'
    ]

    __slots__ += ['front_sidedef', 'back_sidedef']