#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gl_renderer.h"
#include "texture.h"


#define MAX_VERTICES 2000

static float* vertices[MAX_TEXTURES];
static float* texs[MAX_TEXTURES];

static int current_texture;
static int current_vertex[MAX_TEXTURES];

void gl_do_frame()
{
	int i,j;
	glClear(GL_COLOR_BUFFER_BIT);

	for(i=0; i<MAX_TEXTURES; i++)
	{
		int cv;
		if(!is_texture_allocated(i))
			continue;

		cv = current_vertex[i];

		bind_texture(i);
		glBegin(GL_QUADS);
		for(j=0;j<cv; j++)
		{
			float* v = &vertices[i][3*j];
			float* t = &texs[i][2*j];

			glTexCoord2fv(t);
			glVertex3fv(v);
		}
		glEnd();

		current_vertex[i]=0;
	}
}

void gl_bind_texture(int id)
{
	if(!is_texture_allocated(id))
	{
		printf("Tried to bind a missing texture %d\n", id);
		return;
	}
	current_texture = id;
}

void gl_vertex(float v1, float v2, float v3, float u, float v)
{
	float* ver;
	float* t;
	int cv = current_vertex[current_texture];

	if(cv == MAX_VERTICES)
	{
		printf("Exceeded maximum ammount of vertices\n");
		exit(0);
		return;
	}
	ver = &vertices[current_texture][cv*3];
	t = &texs[current_texture][cv*2];
	ver[0] = v1;
	ver[1] = v2;
	ver[2] = v3;
	t[0] = u;
	t[1] = v;

	current_vertex[current_texture]+=1;
}

void gl_init()
{
	int i;
	memset(current_vertex, 0, sizeof(current_vertex));
	for(i=0;i<MAX_TEXTURES; i++)
	{
		vertices[i] = (float*)malloc(3*MAX_VERTICES*sizeof(float));
		texs[i] = (float*)malloc(2*MAX_VERTICES*sizeof(float));
	}
	glClearColor(0.7f, 0.7f, 1.0f, 0.0f);

	glViewport(0,0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_TEXTURE_2D);

}

void gl_shutdown()
{
	int i;
	for(i=0; i<MAX_TEXTURES; i++)
	{
		free(vertices[i]);
		free(texs[i]);
	}
}


