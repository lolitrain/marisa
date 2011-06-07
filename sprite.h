#ifndef SPRITE_H
#define SPRITE_H

struct sprite 
{
	float width, height;
	int texture;
};

void sprite_draw(struct sprite* s, float cx, float cy);
#endif
