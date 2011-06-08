import bulletmanager
import timer
import textures
from sprite import Sprite
import random
import scriptmanager
from scriptmanager import coroutine
from fps_counter import *

class TestEmmiter1:
    def __init__(self):
        self.sprite = Sprite(textures.get("smile"), (64,64))

    @coroutine
    def do_frame(self):
        max_bullets = 1
        for f in timer.wait(15000):
            for w in timer.wait(1000):
                yield

            for i in range(max_bullets):
                bulletmanager.add_bullet(self.sprite, (400, 300), (random.randint(0, 800), random.randint(0, 600)), 0.3)
            
            if max_bullets < 64:
                max_bullets  = max_bullets*2

class TestEmmiter2:
    def __init__(self, max_bullets):
        self.sprites = (Sprite(textures.get("inv_smile"), (32, 32)), Sprite(textures.get("smile"), (32, 32)))
        self.max_bullets = max_bullets

    @coroutine
    def do_frame(self):
        while True:
            add_bullets = self.max_bullets - bulletmanager.bullet_count()
            if add_bullets > 0:
                for i in range(add_bullets):
                    bulletmanager.add_bullet(self.sprites[random.randint(0, 1)], \
                                          (random.randint(0, 800), random.randint(0, 600)), \
                                              (random.randint(0, 800), random.randint(0, 600)), random.random())
            yield


        
class TestStage:
    def __init__(self):
#        self.test_emmiter1 = TestEmmiter1()
        self.test_emmiter2 = TestEmmiter2(512)
        self. fps_counter = FpsCounter()
        
    @coroutine
    def do_frame(self):
        scriptmanager.add_script(self.test_emmiter2)
        scriptmanager.add_script(self.fps_counter)
 #       for w in timer.wait(11000): yield
  #      scriptmanager.add_script(self.test_emmiter2)
        while True:
            yield
