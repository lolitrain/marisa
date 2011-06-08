#ifndef BULLETS_H
#define BULLETS_H

struct vector2d
{
	float vec[2];
};

struct simple_bullet
{
	struct sprite* sprite;
	struct vector2d pos, velocity;
	struct list_head list;
};

int bullet_create(struct sprite* s, struct vector2d start, struct vector2d headto, float speed);
void bullet_destroy(struct simple_bullet* b);
void bullet_do_frame(struct simple_bullet* b);
void bullet_draw(struct simple_bullet* b);

int bullets_count();
void bullets_draw();
void bullets_do_frame();
void bullets_shutdown();

#endif
