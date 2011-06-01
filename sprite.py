import textures
from textures import Texture
from OpenGL.GL import *

class Sprite:
    def __init__(self, texture, dims):
        self.texture = texture
        self.width = dims[0]
        self.height = dims[1]

    def draw(self, pos):
        self.texture.bind()
        glPushMatrix()
        glTranslate(pos[0], pos[1], 0)
        glBegin(GL_QUADS)
        glTexCoord(0,0)
        glVertex(-self.width/2, -self.height/2)
        glTexCoord(0,1)
        glVertex(-self.width/2, self.height/2)
        glTexCoord(1,1)
        glVertex(self.width/2, self.height/2)
        glTexCoord(1,0)
        glVertex(self.width/2, -self.height/2)
        glEnd()
        glPopMatrix()
