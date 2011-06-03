import timer
import textures
from font import *
from scriptmanager import coroutine
import collections

active_console=None

class Console:
    def __init__(self):
        global active_console
        if active_console:
            raise Exception("Only one console is permitted")

        self.buffer = collections.deque()
        active_console = self
        
        self.font = Font(textures.get("console_font"), 8, 16, 47)
    
        
    def write(self, text):
        if len(self.buffer) >= 10:
            self.buffer.pop()
            
        self.buffer.appendleft(text)

    @coroutine
    def do_frame(self):
        while True:
            for w in timer.wait(5000): yield
            if len(self.buffer) > 0:
                self.buffer.pop()

    def draw(self):
        offset = 0
        for line in self.buffer:
            self.font.show_text((0, offset), line)
            offset += self.font.fheight


        
def write(text):
    global active_console
    if active_console:
        active_console.write(text)
    else:
        print text
