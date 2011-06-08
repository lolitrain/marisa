#ifndef LIST_H
#define LIST_H

#include <stddef.h>

#define container_of(ptr, type, member) ({ \
                const typeof( ((type *)0)->member ) *__mptr = (ptr); \
                (type *)( (char *)__mptr - offsetof(type,member) );})

struct list_head
{
	struct list_head* prev, *next;
};

#define INIT_LIST_HEAD(name) { &(name), &(name) };

static inline void LIST_HEAD_INIT(struct list_head* entry)
{
	entry->prev = entry->next = entry;
}

static inline void __list_add(struct list_head* new, struct list_head* prev, struct list_head* next)
{
	new->next = next;
	next->prev = new;
	new->prev = prev;
	prev->next = new;
}

static inline void list_add_tail(struct list_head* new, struct list_head* head)
{
	__list_add(new, head->prev, head);
}

static inline void __list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
	prev->next = next;
}

static inline void list_del(struct list_head* entry)
{
	__list_del(entry->prev, entry->next);
	entry->prev = entry->next = NULL;
}

#define list_entry(ptr, type, member) container_of(ptr, type, member)


/**
 * list_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define list_for_each_entry(pos, head, member)				\
	for (pos = list_entry((head)->next, typeof(*pos), member);	\
	     &pos->member != (head); 	\
	     pos = list_entry(pos->member.next, typeof(*pos), member))


/**
 * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_entry((head)->next, typeof(*pos), member),	\
		n = list_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.next, typeof(*n), member))

#endif
