import pygame
from settings import *

class MapRenderer:
    def __init__(self, engine):
        self.engine = engine
        self.wad_data = engine.wad_data
        self.vertexes = self.wad_data.vertexes
        self.linedefs = self.wad_data.linedefs
        self.x_min, self.x_max, self.y_min, self.y_max = self.get_map_bounds()
        self.vertexes = [pygame.math.Vector2(self.remap_x(v.x), self.remap_y(v.y))
                         for v in self.vertexes]

    def draw(self):
        self.draw_linedefs()
        #self.draw_vertexes()
        self.draw_player_pos()
        self.draw_node(node_id=self.engine.bsp.root_node_id)

    def draw_bbox(self, bbox, color):
        x, y = self.remap_x(bbox.left), self.remap_y(bbox.top)
        w, h = self.remap_x(bbox.right) - x, self.remap_y(bbox.bottom) - y
        pygame.draw.rect(self.engine.screen, color, (x, y, w, h), 2)

    def draw_node(self, node_id):
        node = self.engine.wad_data.nodes[node_id]
        bbox_front = node.bbox['front']
        bbox_back = node.bbox['back']
        self.draw_bbox(bbox=bbox_front, color='green')
        self.draw_bbox(bbox=bbox_back, color='red')

        x1, y1 = self.remap_x(node.x_partition), self.remap_y(node.y_partition)
        x2 = self.remap_x(node.x_partition + node.dx_partition)
        y2 = self.remap_y(node.y_partition + node.dy_partition)
        pygame.draw.line(self.engine.screen, 'blue', (x1, y1), (x2, y2), 4)

    def draw_player_pos(self):
        pos = self.engine.player.pos
        x = self.remap_x(pos.x)
        y = self.remap_y(pos.y)
        pygame.draw.circle(self.engine.screen, 'orange', (x, y), 8)

    def draw_linedefs(self):
        for line in self.linedefs:
            p1 = self.vertexes[line.start_vertex_id]
            p2 = self.vertexes[line.end_vertex_id]
            pygame.draw.line(self.engine.screen, (70, 70, 70), p1, p2, 3)

    def remap_x(self, n, out_min=30, out_max=WIDTH-30):
        return(max(self.x_min, min(n, self.x_max)) - self.x_min) * (
            out_max - out_min) / (self.x_max - self.x_min) + out_min
    
    def remap_y(self, n, out_min=30, out_max=HEIGHT-30):
        return HEIGHT - (max(self.y_min, min(n, self.y_max)) - self.y_min) * (
            out_max - out_min) / (self.y_max - self.y_min) - out_min

    def get_map_bounds(self):
        x_sorted = sorted(self.vertexes, key=lambda v: v.x)
        x_min, x_max = x_sorted[0].x, x_sorted[-1].x

        y_sorted = sorted(self.vertexes, key=lambda v: v.y)
        y_min, y_max = y_sorted[0].y, y_sorted[-1].y

        return x_min, x_max, y_min, y_max

    def draw_vertexes(self):
        for v in self.vertexes:
            pygame.draw.circle(self.engine.screen, 'white', (v.x, v.y), 4)
