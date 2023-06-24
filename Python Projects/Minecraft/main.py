import math
import random
import ctypes
import pyglet

pyglet.options["shadow_window"] = False
pyglet.options["debug_gl"] = False

import pyglet.gl as gl

import matrix
import shader
import camera

import world

import hit

class Window(pyglet.window.Window):
    def __init__(self, **args):
        super(Window, self).__init__(**args)

        self.world = world.World()
        
        self.shader = shader.Shader("vert.glsl", "frag.glsl")
        self.shader_sampler_location = self.shader.find_uniform(b"texture_array_sampler")
        self.shader.use()

        pyglet.clock.schedule_interval(self.update, 1.0 / 60)
        self.mouse_capture = False

        self.camera = camera.Camera(self.shader, self.width, self.height)

        self.holding = 7

    def update(self, delta_time):
        if not self.mouse_capture:
            self.camera.input = [0, 0, 0]

        self.camera.update_camera(delta_time)
        

    def on_draw(self):
        self.camera.update_matrices()


        gl.glActiveTexture(gl.GL_TEXTURE0)
        gl.glBindTexture(gl.GL_TEXTURE_2D_ARRAY, self.world.texture_manager.texture_array)
        gl.glUniform1i(self.shader_sampler_location, 0)

        gl.glEnable(gl.GL_DEPTH_TEST)
        gl.glEnable(gl.GL_CULL_FACE)
        gl.glClearColor(0.0, 0.0, 0.0, 1.0)
        self.clear()
        self.world.draw()

        gl.glFinish()

    def on_resize(self, width, height):
        print("Resize %d * %d" % (width, height))
        gl.glViewport(0, 0, width, height)
        self.camera.width = width
        self.camera.height = height

    def on_mouse_press(self, x, y, button, modifiers):
        if not self.mouse_capture:
            self.mouse_capture = True
            self.set_exclusive_mouse(self.mouse_capture)

            return

        def hit_callback(current_block, next_block):
            if button == pyglet.window.mouse.RIGHT:
                self.world.set_block(current_block, self.holding)
            elif button == pyglet.window.mouse.LEFT:
                self.world.set_block(next_block, 0)
            elif button == pyglet.window.mouse.MIDDLE:
                self.holding = self.world.get_block_number(next_block)
        
        hit_ray = hit.Hit_ray(self.world, self.camera.rotation, self.camera.position)

        while hit_ray.distance < hit.HIT_RANGE:
            if hit_ray.step(hit_callback):
                break

    def on_mouse_motion(self, x, y, dx, dy):
        if self.mouse_capture:
            sensitivity = 0.004

            self.camera.rotation[0] += dx * sensitivity
            self.camera.rotation[1] += dy * sensitivity

            self.camera.rotation[1] = max(-math.tau / 4, min(math.tau / 4, self.camera.rotation[1]))

    def on_mouse_drag(self, x, y, dx, dy, buttons, modifiers):
        self.on_mouse_motion(x, y, dx, dy)        
    
    def on_key_press(self, key, modifiers):
        if not self.mouse_capture:
            return

        if key == pyglet.window.key.D:
            self.camera.input[0] += 1
        elif key == pyglet.window.key.A:
            self.camera.input[0] -= 1
        elif key == pyglet.window.key.W:
            self.camera.input[2] += 1
        elif key == pyglet.window.key.S:
            self.camera.input[2] -= 1
        
        elif key == pyglet.window.key.SPACE:
            self.camera.input[1] += 1
        elif key == pyglet.window.key.LSHIFT:
            self.camera.input[1] -= 1

        elif key == pyglet.window.key.G:
            self.holding = random.randint(1, len(self.world.block_types) - 1)

        elif key == pyglet.window.key.ESCAPE:
            self.mouse_capture = False
            self.set_exclusive_mouse(False)

     
    def on_key_release(self, key, modifiers):
        if not self.mouse_capture:
            return

        if key == pyglet.window.key.D:
            self.camera.input[0] -= 1
        elif key == pyglet.window.key.A:
            self.camera.input[0] += 1
        elif key == pyglet.window.key.W:
            self.camera.input[2] -= 1
        elif key == pyglet.window.key.S:
            self.camera.input[2] += 1
        
        elif key == pyglet.window.key.SPACE:
            self.camera.input[1] -= 1
        elif key == pyglet.window.key.LSHIFT:
            self.camera.input[1] += 1



class Game:
    def __init__(self):
        self.config = gl.Config(double_buffer = True, major_version = 3, minor_version = 3, depth_size = 16)
        self.window = Window(config = self.config, width = 800, height = 600, caption = "Minecraft Vindle Version P", resizable = True, vsync = False)
    
    def run(self):
        pyglet.app.run()


if __name__ == "__main__":
    game = Game()
    game.run()
