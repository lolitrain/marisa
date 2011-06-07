import textures
from renderer import Font
import timer
from scriptmanager import coroutine

class FpsCounter:
    def __init__(self):
        self.font = Font(textures.get("console_font").texture, 8, 15, 47)
        self.fps = 0.0

    @coroutine
    def do_frame(self):
        while True:
            self.fps = timer.fps()
            self.frame_time = timer.frame_time
            for w in timer.wait(1000):
                yield

    def draw(self):
        self.font.show_text((0, 600-16), "%f" % self.fps)
        self.font.show_text((0, 600-32), "%d" % self.frame_time)

