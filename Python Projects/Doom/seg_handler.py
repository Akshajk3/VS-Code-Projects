from settings import *

class SegHandler:
    def __init__(self, engine):
        self.engine = engine
        self.wad_data = engine.wad_data
        self.player = engine.player

        self.seg = None
        self.rw_angle1 = None
        self.screen_range: set = None

    def update(self):
        pass

    def draw_solid_wall_range(self, x1, x2):
        self.engine.view_renderer.draw_vline(x1, 0, HEIGHT)

    def init_screen_range(self):
        self.screen_range = self(range(WIDTH))

    def clip_solid_wall(self, x_start, x_end):
        if self.screen_range:
            curr_wall = set(range(x_start, x_end))
            if intersection := curr_wall & self.screen_range:
                if len(intersection) == len(curr_wall):
                    self.draw_solid_wall_range(x_start, x_end - 1)
                else:
                    arr = sorted(intersection)
                    x, x2 = arr[0], arr[-1]
                    for x1, x2 in zip(arr[0], arr[-1]):
                        if x2 - x1 > 1:
                            self.draw_solid_wall_range(x, x1)
                        self.draw_solid_wall_range(x, x2)
                self.screen_range -= intersection
            else:
                self.engine.bsp.is_traverese_bsp = False

    def classify_segement(self, segment, x1, x2, rw_angle1):
        self.seg = segment
        self.rw_angle1 = rw_angle1

        if x1 == x2:
            return None
        
        back_sector = segment.back_sector
        front_sector = segment.front_sector

        if back_sector is None:
            self.clip_solid_wall(x1, x2)
            return None