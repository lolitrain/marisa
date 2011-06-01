import video
import functools
import bulletmanager
import timer
from bulletmanager import SimpleBullet
import textures
from sprite import *
import random
from fps_counter import FpsCounter
from OpenGL.GL import *

class TestEmmiter:
    def __init__(self):
        self.sprite = Sprite(textures.get("smile"), (64,64))

    def draw(self):
        pass

    def do_frame(self):
        max_bullets = 1
        while True:
            for w in timer.wait(1000):
                yield

            for i in range(max_bullets):
                bullet = SimpleBullet(self.sprite, (400, 300), (random.randint(0, 800), random.randint(0, 600)), 0.5)
                bulletmanager.add_bullet(bullet)
            
            if max_bullets < 64:
                max_bullets  = max_bullets*2
            
            start = timer.gettime()

        

class TestScript:
    def __init__(self):
        video.add_draw_hook(getattr(self, "draw"))
        self.script = TestEmmiter()
        self.script_frame = self.script.do_frame()
        self.counter = FpsCounter()
        self.counter_frame = self.counter.do_frame()
            
    def draw(self):
        self.counter.draw()
        bulletmanager.draw()
        error = glGetError()
        if error == GL_NO_ERROR:
            pass
        else:
            print error

    def do_frame(self):
        self.script_frame.next()
        self.counter_frame.next()
        bulletmanager.do_frame()
