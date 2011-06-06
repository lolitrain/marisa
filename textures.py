import console
import video
import renderer

class Texture:
  def __init__(self, filename):
    self.texture = renderer.load_texture(filename)
    self.width = renderer.texture_width(self.texture)
    self.height = renderer.texture_height(self.texture)

  def __del__(self):
    renderer.free_texture(self.texture)

  def bind(self):
    renderer.bind(self.texture)

textures = {}

def get(name):
    if name in textures:
        return textures[name]

    texture = Texture(name +".png")
    textures[name] = texture
    return texture

def clear():
    textures.clear()
