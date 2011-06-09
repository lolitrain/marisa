#include <Python.h>
#include <GL/gl.h>

#include <math.h>

#include <stdio.h>

#include "gl_math.h"
#include "list.h"
#include "sprite.h"
#include "gl_renderer.h"

void sprite_draw(struct sprite* s, float cx, float cy, float angle)
{
	float w2 = s->width/2;
	float h2 = s->height/2;
	int i;
	float sint = sin(torad(angle));
	float cost = cos(torad(angle));
	struct matrix2d rotation = { {
		{cost, -sint},
		{sint, cost} }};
	struct vector2d v[4] = { {{-w2, -h2}}, {{-w2, h2}}, {{w2, h2}}, {{w2,-h2}} };

	for(i=0; i<4;i++)
	{
		v[i] = matrix_vec_mult(rotation.m, v[i].vec);
	}

	for(i=0; i<4;i++)
	{
		v[i].vec[0] += cx;
		v[i].vec[1] += cy;
	}

	gl_bind_texture(s->texture);

	gl_vertex(v[0].vec[0], v[0].vec[1], 0, 0,0);
	gl_vertex(v[1].vec[0], v[1].vec[1], 0, 0,1);
	gl_vertex(v[2].vec[0], v[2].vec[1], 0, 1,1);
	gl_vertex(v[3].vec[0], v[3].vec[1], 0, 1,0);
}





