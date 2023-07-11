from pyglet import image
from pyglet import sprite

class Crosshair:
    def __init__(self, crosshair_path, window_width, window_height):
        self.path = crosshair_path
        self.pic = image.load(crosshair_path)
        self.window_width = window_width
        self.window_height = window_height
        self.sprite = sprite.Sprite(self.pic, self.window_width/2, self.window_height/2)


    def draw(self):
        self.sprite.draw()
