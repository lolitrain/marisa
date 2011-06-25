import scriptmanager
from scriptmanager import coroutine
from sprite import *
import textures
import fps_counter
from vector import *
import inputmanager
import bulletmanager
from pygame.locals import *
from math import *
from renderer import ftime
import timer

class PlayerScript:
    def __init__(self):
        self.sprite = Sprite(textures.get("smile"), (64,64))
        self.pos = [400, 300]
        self.angle = 90
        self.angular_velocity = 0;
        self.acceleration = 0
        self.speed = 0
        self.shot_script = PlayerShot(self)

        inputmanager.bind(K_LEFT, getattr(self, "rotate_left"))
        inputmanager.bind(K_RIGHT, getattr(self, "rotate_right"))
        inputmanager.bind(K_UP, getattr(self, "thrust_forward"))
        inputmanager.bind(K_DOWN, getattr(self, "thrust_back"))
        inputmanager.bind(K_z, getattr(self, "shoot"))

    def shoot(self, active):
        if active:
            scriptmanager.add_script(self.shot_script)
        else:
            scriptmanager.remove_script(self.shot_script)

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

            self.pos = [self.pos[0] + self.speed*ftime()*cos(radians(self.angle)), self.pos[1]+self.speed*ftime()*sin(radians(self.angle))]
            
            if self.pos[0] < 0: self.pos[0] += 800
            elif self.pos[0] > 800: self.pos[0] -= 800

            if self.pos[1] < 0: self.pos[1] += 600
            elif self.pos[1] > 600: self.pos[1] -= 600
            yield

    def draw(self):
        self.sprite.draw(self.pos, self.angle-90)


class PlayerShot:
        def __init__(self, player):
            self.player = player
            self.bullet = Sprite(textures.get("inv_smile"), (10, 10))

        @coroutine
        def do_frame(self):
            while(True):
                bulletmanager.add_bullet_angle(self.bullet, self.player.pos, self.player.angle, self.player.speed+400)
                
                for w in timer.wait(100):
                    yield

                    

class DemoStage:
    def __init__(self):
        scriptmanager.add_script(PlayerScript())
        scriptmanager.add_script(fps_counter.FpsCounter())

