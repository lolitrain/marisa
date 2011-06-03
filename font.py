from OpenGL.GL import *

class Font:
    def __init__(self, texture, fwidth, fheight, chars_per_line):
        self.texture = texture
        self.fwidth = fwidth
        self.fheight = fheight
        self.chars_per_line = chars_per_line

    def show_text(self, pos, text):
        self.texture.bind()
        current_pos = list(pos)
        for c in text:
            self.show_glyph(current_pos, c)
            current_pos[0] += self.fwidth

    def show_glyph(self, pos, glyph):
        glyph_offset = ord(glyph) - 33
        glyph_line = glyph_offset / self.chars_per_line
        glyph_line_offset = glyph_offset % self.chars_per_line
        u1 = float(glyph_line_offset*self.fwidth) / self.texture.width
        u2 = float((glyph_line_offset+1) * self.fwidth) / self.texture.width
        v1 = 1-(float((glyph_line+1) * self.fheight) / self.texture.height)
        v2 = 1-(float(glyph_line*self.fheight) / self.texture.height)

        glPushMatrix()
        glTranslate(pos[0], pos[1], 0.5)
        glBegin(GL_QUADS)
        glTexCoord(u1, v1)
        glVertex(0, 0)
        glTexCoord(u1, v2)
        glVertex(0, self.fheight)
        glTexCoord(u2, v2)
        glVertex(self.fwidth, self.fheight)
        glTexCoord(u2, v1)
        glVertex(self.fwidth, 0)
        glEnd()
        glPopMatrix()
