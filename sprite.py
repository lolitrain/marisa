import textures
from textures import Texture
from OpenGL.GL import *

class Sprite:
    def __init__(self, texture, dims, pos):
        self.texture = texture
        self.width = dims[0]
        self.height = dims[1]
        self.pos = pos

    def draw(self):
        glPushMatrix()
        glTranslate(self.pos[0], self.pos[1], 0)
        self.texture.bind()
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
