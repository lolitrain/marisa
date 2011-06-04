import textures
from textures import Texture
import video

class Sprite:
    def __init__(self, texture, dims):
        self.texture = texture
        self.width = dims[0]
        self.height = dims[1]

    def draw(self, pos):
        self.texture.bind()

        x1 = pos[0] - self.width/2
        y1 = pos[1] - self.height/2
        x2 = pos[0] + self.width/2
        y2 = pos[1] + self.height/2

        video.vertex((x1, y1, 0), (0,0))
        video.vertex((x1, y2, 0), (0,1))
        video.vertex((x2, y2, 0), (1,1))
        video.vertex((x2, y1, 0), (1,0))
