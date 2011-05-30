import video
import functools
import bulletmanager
import timer
from bulletmanager import SimpleBullet
import textures
from sprite import *
import random


# waits returns after a certain number of milliseconds
def wait(msec):
    start = timer.gettime()
    current_time = timer.gettime()
    while current_time - start < msec:
        yield
        current_time = timer.gettime();
    

class TestEmmiter:
    def __init__(self):
        self.sprite = Sprite(textures.get("smile"), (64,64))

    def draw(self):
        pass

    def do_frame(self):
#        start = timer.gettime()
        max_bullets = 1
        while True:
 #           current_time = timer.gettime()
  #          while current_time-start < 1000:
   #             yield
    #            current_time = timer.gettime()
            for w in wait(1000):
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
        self.emmiter = TestEmmiter()
        gen = self.emmiter.do_frame()
        self.emmiter_frame_function = getattr(gen, "next")

    def draw(self):
        bulletmanager.draw()

    def do_frame(self):
        self.emmiter_frame_function()
        bulletmanager.do_frame()
