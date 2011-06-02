import textures
from font import *
import timer

class FpsCounter:
    def __init__(self):
        self.font = Font(textures.get("console_font"), 8, 15, 47)
        self.fps = 0.0

    def do_frame(self):
        while True:
            self.fps = timer.fps()
            for w in timer.wait(1000):
                yield

    def draw(self):
        self.font.show_text((0, 600-16), "%f" % self.fps)

