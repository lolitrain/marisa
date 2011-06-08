import scriptmanager
from scriptmanager import coroutine
from sprite import *
import textures
import fps_counter
from vector import *
import inputmanager
from pygame.locals import *

class PlayerScript:
    def __init__(self):
        self.sprite = Sprite(textures.get("smile"), (64,64))
        self.pos = (400, 300)

        inputmanager.bind(K_UP, getattr(self, "do_up"))

    def draw(self):
        self.sprite.draw(self.pos)

    def do_up(self, activate):
        if activate:
            self.pos = (400, 500)
        else:
            self.pos = (400, 300)

    

class DemoStage:
    def __init__(self):
        scriptmanager.add_script(PlayerScript())
        scriptmanager.add_script(fps_counter.FpsCounter())

