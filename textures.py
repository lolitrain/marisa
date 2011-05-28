import pygame
from OpenGL.GL import *

class Texture:
  def __init__(self, filename):
    surface = pygame.image.load(filename)
    data = pygame.image.tostring(surface, "RGBA", 1)
    width = surface.get_width()
    height = surface.get_height()
    self.texture = glGenTextures(1)
    glBindTexture(GL_TEXTURE_2D, self.texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, \
                   GL_UNSIGNED_BYTE, data)

  def __del__(self):
      glDeleteTextures([self.texture])

  def bind(self):
      glBindTexture(GL_TEXTURE_2D, self.texture)

textures = {}

def get(name):
    if name in textures:
        return textures[name]

    texture = Texture(name +".png")
    textures[name] = texture
    return texture

def clear():
    textures.clear()