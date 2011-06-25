#include <Python.h>

#include "list.h"
#include "bullets.h"
#include "sprite.h"
#include "gl_math.h"
#include "timer.h"

static struct list_head bullet_list = INIT_LIST_HEAD(bullet_list);
static int bullet_count = 0;

int bullet_create(struct sprite* s, struct vector2d start, struct vector2d headto, float speed)
{
	struct simple_bullet* b;

	b = (struct simple_bullet*)malloc(sizeof(*b));
	if(!b)
		return -1;

	LIST_HEAD_INIT(&b->list);
	b->sprite = s;
	b->pos = start;
	b->velocity = scalar_mult(normalize(vec_sub(headto, start)), speed);

	list_add_tail(&b->list, &bullet_list);
	bullet_count++;
	
//	printf("Added bullet with texture %d %p, %d\n", s->texture, b, bullet_count);
	return 0;
}

void bullet_destroy(struct simple_bullet* b)
{
	list_del(&b->list);
	
	put_sprite(b->sprite);
	free(b);

	bullet_count--;
//	printf("Destroying bullet %p %d\n", b, bullet_count);

}

void bullet_do_frame(struct simple_bullet* b)
{
	b->pos = vec_add(b->pos, scalar_mult(b->velocity, timer_get_time()));
}

void bullet_draw(struct simple_bullet* b)
{
	sprite_draw(b->sprite, b->pos.vec[0], b->pos.vec[1], 0);
}

int bullets_count()
{
	return bullet_count;
}

void bullets_draw()
{
	struct simple_bullet* b;
	list_for_each_entry(b, &bullet_list, list)
	{
		bullet_draw(b);
	}
}

void bullets_do_frame()
{
	struct simple_bullet* b, *n;

	list_for_each_entry_safe(b, n, &bullet_list, list)
	{
		bullet_do_frame(b);

		if(b->pos.vec[0] < 0 || b->pos.vec[0] > 800 || b->pos.vec[1] < 0 || b->pos.vec[1] > 600)
		{
			bullet_destroy(b);
		}
	}

}

void bullets_shutdown()
{
	struct simple_bullet* b, *n;
	list_for_each_entry_safe(b,n, &bullet_list, list)
	{
		bullet_destroy(b);
	}
}

