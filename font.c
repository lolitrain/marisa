#include <string.h>
#include <stdio.h>

#include "font.h"
#include "texture.h"
#include "gl_renderer.h"

    /* def show_glyph(self, pos, glyph): */
    /*     glyph_offset = ord(glyph) - 33 */
    /*     glyph_line = glyph_offset / self.chars_per_line */
    /*     glyph_line_offset = glyph_offset % self.chars_per_line */
    /*     u1 = float(glyph_line_offset*self.fwidth) / self.texture.width */
    /*     u2 = float((glyph_line_offset+1) * self.fwidth) / self.texture.width */
    /*     v1 = 1-(float((glyph_line+1) * self.fheight) / self.texture.height) */
    /*     v2 = 1-(float(glyph_line*self.fheight) / self.texture.height) */

    /*     x1 = pos[0] */
    /*     x2 = pos[0]+self.fwidth */
    /*     y1 = pos[1] */
    /*     y2 = pos[1]+self.fheight */

    /*     vertex((x1, y1, 0), (u1,v1)) */
    /*     vertex((x1, y2, 0), (u1,v2)) */
    /*     vertex((x2, y2, 0), (u2,v2)) */
    /*     vertex((x2, y1, 0), (u2,v1)) */

static void font_show_glypth(struct font* f, char c, float bx, float by)
{
	int offset = c - 33;
	int line = offset/f->chars_per_line;
	int line_offset = offset % f->chars_per_line;

	float u1 = line_offset*f->cwidth / (float)get_texture_width(f->texture);
	float u2 = (line_offset+1)*f->cwidth / (float)get_texture_width(f->texture);
	float v1 = 1 - (line+1)*f->cheight/(float)get_texture_height(f->texture);
	float v2 = 1 - line*f->cheight/(float)get_texture_height(f->texture);

	float x1 = bx;
	float x2 = bx+f->cwidth;
	float y1 = by;
	float y2 = by+f->cheight;

	gl_vertex(x1, y1, 0, u1,v1);
        gl_vertex(x1, y2, 0, u1,v2);
        gl_vertex(x2, y2, 0, u2,v2);
        gl_vertex(x2, y1, 0, u2,v1);
}

void font_show_text(struct font* f, const char* str, float bx, float by)
{
	int i;
	int len;

	len = strlen(str);
	gl_bind_texture(f->texture);

	for(i=0; i<len; i++)
	{
		font_show_glypth(f, str[i], bx+f->cwidth*i, by);
	}
}
