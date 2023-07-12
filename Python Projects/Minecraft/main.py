import math
import random
import ctypes
import pyglet

pyglet.options["shadow_window"] = False
pyglet.options["debug_gl"] = False

import pyglet.gl as gl

import matrix
import shader
import player

import world
    
import hit

import crosshair

from time import time

class Window(pyglet.window.Window):
    def __init__(self, **args):
        super(Window, self).__init__(**args)

        self.world = world.World()
        
        self.shader = shader.Shader("vert.glsl", "frag.glsl")
        self.shader_sampler_location = self.shader.find_uniform(b"texture_array_sampler")
        self.shader.use()

        pyglet.clock.schedule_interval(self.update, 1.0 / 60)
        self.mouse_capture = False

        self.sprinting = False

        self.show_fps = False

        self.player = player.Player(self.world, self.shader, self.width, self.height)

        self.crosshair = pyglet.text.Label("+", x = self.width / 2, y = self.height / 2,
				font_size = 16,
				color = (255, 255, 255, 255),
				width = self.width // 3,
				multiline = True
		)

        self.holding = 7

        self.fps = pyglet.text.Label("", x = 10, y = self.height - 20,
				font_size = 16,
				color = (255, 255, 255, 255),
				width = self.width // 3,
				multiline = True
		)
    
    def update_fps(self, delta_time):
        self.fps.text = f"{round(1 / delta_time)} FPS"    

    def update(self, delta_time):
        if self.show_fps:
            self.update_fps(delta_time)

        if not self.mouse_capture:
            self.player.input = [0, 0, 0]

        self.player.update(delta_time)

        if self.sprinting:
            self.player.target_speed = player.SPRINTING_SPEED
        else:
            self.player.target_speed
        

    def on_draw(self):
        self.player.update_matrices()

        gl.glActiveTexture(gl.GL_TEXTURE0)
        gl.glBindTexture(gl.GL_TEXTURE_2D_ARRAY, self.world.texture_manager.texture_array)
        gl.glUniform1i(self.shader_sampler_location, 0)

        gl.glEnable(gl.GL_DEPTH_TEST)
        gl.glEnable(gl.GL_CULL_FACE)
        gl.glClearColor(0.0, 0.0, 0.0, 1.0)
        self.clear()
        self.world.draw()
        if self.show_fps:
            self.fps.draw()
        #self.crosshair.draw()
        gl.glFinish()

    def on_resize(self, width, height):
        print("Resize %d * %d" % (width, height))
        gl.glViewport(0, 0, width, height)
        self.player.view_width = width
        self.player.view_height = height
        self.crosshair.window_width = width
        self.crosshair.window_height = height

    def on_mouse_press(self, x, y, button, modifiers):
        if not self.mouse_capture:
            self.mouse_capture = True
            self.set_exclusive_mouse(self.mouse_capture)

            return

        def hit_callback(current_block, next_block):
            if button == pyglet.window.mouse.RIGHT:
                self.world.try_set_block(current_block, self.holding, self.player.collider)
            elif button == pyglet.window.mouse.LEFT:
                self.world.set_block(next_block, 0)
            elif button == pyglet.window.mouse.MIDDLE:
                self.holding = self.world.get_block_number(next_block)

        x, y, z = self.player.position
        y += self.player.eye_level
        
        hit_ray = hit.Hit_ray(self.world, self.player.rotation, (x, y, z))

        while hit_ray.distance < hit.HIT_RANGE:
            if hit_ray.step(hit_callback):
                break

    def on_mouse_motion(self, x, y, dx, dy):
        if self.mouse_capture:
            sensitivity = 0.004

            self.player.rotation[0] += dx * sensitivity
            self.player.rotation[1] += dy * sensitivity

            self.player.rotation[1] = max(-math.tau / 4, min(math.tau / 4, self.player.rotation[1]))

    def on_mouse_drag(self, x, y, dx, dy, buttons, modifiers):
        self.on_mouse_motion(x, y, dx, dy)        
    
    def on_key_press(self, key, modifiers):
        if not self.mouse_capture:
            return

        if key == pyglet.window.key.D:
            self.player.input[0] += 1
        elif key == pyglet.window.key.A:
            self.player.input[0] -= 1
        elif key == pyglet.window.key.W:
            self.player.input[2] += 1
        elif key == pyglet.window.key.S:
            self.player.input[2] -= 1
        
        elif key == pyglet.window.key.SPACE:
            self.player.input[1] += 1
        elif key == pyglet.window.key.LSHIFT:
            self.player.input[1] -= 1
        elif key == pyglet.window.key.LCTRL:
            self.player.target_speed = player.SPRINTING_SPEED

        elif key == pyglet.window.key.F:
            self.player.flying = not self.player.flying

        elif key == pyglet.window.key.F3:
            self.show_fps = not self.show_fps

        elif key == pyglet.window.key.G:
            self.holding = random.randint(1, len(self.world.block_types) - 1)

        elif key == pyglet.window.key.O:
            self.world.save.save()

        elif key == pyglet.window.key.ESCAPE:
            self.mouse_capture = False
            self.set_exclusive_mouse(False)

     
    def on_key_release(self, key, modifiers):
        if not self.mouse_capture:
            return

        if key == pyglet.window.key.D:
            self.player.input[0] -= 1
        elif key == pyglet.window.key.A:
            self.player.input[0] += 1
        elif key == pyglet.window.key.W:
            self.player.input[2] -= 1
        elif key == pyglet.window.key.S:
            self.player.input[2] += 1
        
        elif key == pyglet.window.key.SPACE:
            self.player.input[1] -= 1
        elif key == pyglet.window.key.LSHIFT:
            self.player.input[1] += 1
        elif key == pyglet.window.key.LCTRL:
            self.player.target_speed = player.WALKING_SPEED



class Game:
    def __init__(self):
        self.config = gl.Config(double_buffer = True, major_version = 3, minor_version = 3, depth_size = 16)
        self.window = Window(config = self.config, width = 800, height = 600, caption = "Minecraft Vindle Version P", resizable = True, vsync = False)
    
    def run(self):
        pyglet.app.run()


if __name__ == "__main__":
    game = Game()
    game.run()
