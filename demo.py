import scriptmanager
from scriptmanager import coroutine
from sprite import *
import textures
import fps_counter
from vector import *
import inputmanager
from pygame.locals import *
from math import *
import timer

def ftime():
    return timer.frame_time/float(1000)

class PlayerScript:
    def __init__(self):
        self.sprite = Sprite(textures.get("smile"), (64,64))
        self.pos = (400, 300)
        self.angle = 90
        self.angular_velocity = 0;
        self.acceleration = 0
        self.speed = 0

        inputmanager.bind(K_LEFT, getattr(self, "rotate_left"))
        inputmanager.bind(K_RIGHT, getattr(self, "rotate_right"))
        inputmanager.bind(K_UP, getattr(self, "thrust_forward"))
        inputmanager.bind(K_DOWN, getattr(self, "thrust_back"))

    def thrust_forward(self, active):
        if active: self.acceleration = 100
        else: self.acceleration = 0

    def thrust_back(self, active):
        if active: self.acceleration = -100
        else: self.acceleration = 0
        
    def rotate_left(self, active): 
        if active:
            self.angular_velocity += 4
        else:
            self.angular_velocity -= 4
            
    def rotate_right(self, active):
        if active:
            self.angular_velocity -= 4
        else:
            self.angular_velocity += 4

    @coroutine
    def do_frame(self):
        while True:
            self.angle += self.angular_velocity
            if self.angle > 360:
                self.angle -= 360
            elif self.angle < 0:
                self.angle += 360

            self.speed += self.acceleration*ftime()
            if self.speed > 300: self.speed = 300
            if self.speed < 0: self.speed = 0

            self.pos = (self.pos[0] + self.speed*ftime()*cos(radians(self.angle)), self.pos[1]+self.speed*ftime()*sin(radians(self.angle)))
            yield

    def draw(self):
        self.sprite.draw(self.pos, self.angle-90)

    def do_up(self, activate):
        if activate:
            self.pos = (400, 500)
        else:
            self.pos = (400, 300)

    

class DemoStage:
    def __init__(self):
        scriptmanager.add_script(PlayerScript())
        scriptmanager.add_script(fps_counter.FpsCounter())

