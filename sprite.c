#include <GL/gl.h>

#include "sprite.h"
#include "gl_renderer.h"

void sprite_draw(struct sprite* s, float cx, float cy)
{
	float x1 = cx - s->width/2;
	float y1 = cy - s->height/2;
	float x2 = cx + s->width/2;
	float y2 = cy + s->height/2;

	gl_bind_texture(s->texture);

	gl_vertex(x1, y1, 0, 0,0);
	gl_vertex(x1, y2, 0, 0,1);
	gl_vertex(x2, y2, 0, 1,1);
	gl_vertex(x2, y1, 0, 1,0);
}





