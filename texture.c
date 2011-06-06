#include <GL/gl.h>
#include <png.h>
#include <stdio.h>
#include <stdlib.h>

#include "texture.h"

struct texture
{
	GLuint id;
	unsigned int width, height;
	void* pixels;
};

static int read_png_pixels(FILE* infile, struct texture* t)
{
	unsigned char sig[8];
	png_uint_32 width, height;
	int bit_depth, color_type;
	png_structp png_ptr;
	png_infop info_ptr;
	png_bytep pixel_data;
	png_bytepp row_pointers;
	unsigned int i;
	

	fread(sig, 1, 8, infile);

	if(!png_check_sig(sig, 8))
		return -1;

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(!png_ptr)
		return -4;

	info_ptr = png_create_info_struct(png_ptr);
	if(!info_ptr)
	{
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return -4;
	}

	if(setjmp(png_ptr->jmpbuf))
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		return -2;
	}

	png_init_io(png_ptr, infile);
	png_set_sig_bytes(png_ptr, 8);
	
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, 
		     &color_type, NULL, NULL, NULL);

	// Expect only the png files in the required format
	if(bit_depth != 8 || color_type != PNG_COLOR_TYPE_RGB_ALPHA)
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		return -1;
	}

	t->width = width;
	t->height = height;

	pixel_data = t->pixels = (png_bytep)malloc(4*width*height*sizeof(png_bytep));
	row_pointers = png_get_rows(png_ptr, info_ptr);
	// for some reason png image seems to be upside down
	for(i=0; i<height; i++)
	{
		memcpy(pixel_data + 4*width*i, row_pointers[height-1-i], 4*width);
	}

	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	
	return 0;
	
}

static struct texture textures[MAX_TEXTURES];
static int free_textures[MAX_TEXTURES];

void init_textures()
{
	memset(free_textures, 0, sizeof(free_textures));
}

static int get_free_texture()
{
	int i;
	for(i=0; i<MAX_TEXTURES; i++)
	{
		if(!free_textures[i]) return i;
	}

	return -1;
}

static void get_texture(int id)
{
	free_textures[id] = 1;
}

int is_texture_allocated(int id)
{
	return free_textures[id];
}

int alloc_texture(const char* filename)
{
	FILE* f;
	int err = -1;
	int id;
	struct texture* t;

	id = get_free_texture();
	if(id < 0)
		goto out;
	t = &textures[id];

	f=fopen(filename, "rb");
	if(!f)
		goto out;

	if((err = read_png_pixels(f, t)) < 0)
		goto file;

	glGenTextures(1, &t->id);
	glBindTexture(GL_TEXTURE_2D, t->id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t->width, t->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, t->pixels);

	free(t->pixels);

	get_texture(id);
	err=id;

	printf("Bound %s to as %d\n", filename, id);

file:
	fclose(f);
out:
	return err;
}

void free_texture(int id)
{
	struct texture* t = &textures[id];
	glDeleteTextures(1, &t->id);
	free_textures[id] = 0;
}

void bind_texture(int id)
{
	struct texture* t = &textures[id];
	glBindTexture(GL_TEXTURE_2D, t->id);
}

int get_texture_width(int id)
{
	return textures[id].width;
}

int get_texture_height(int id)
{
	return textures[id].height;
}




