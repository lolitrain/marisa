#ifndef SPRITE_H
#define SPRITE_H

struct sprite 
{
	float width, height;
	int texture;
};

struct py_sprite {
	PyObject_HEAD
	/* Type-specific fields go here. */
	struct sprite s;
};


void sprite_draw(struct sprite* s, float cx, float cy);

static inline void get_sprite(struct sprite* s)
{
	Py_INCREF(container_of(s, struct py_sprite, s));
}

static inline void put_sprite(struct sprite* s)
{
	Py_DECREF(container_of(s, struct py_sprite, s));
}
#endif
