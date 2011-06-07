from renderer import vertex
import renderer

class Sprite:
    def __init__(self, texture, dims):
        self.sprite = renderer.Sprite(dims[0],dims[1], texture.texture)
        self.draw = getattr(self.sprite, "draw")

