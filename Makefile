CFLAGS=-Wall -I/usr/include/python2.7
LDFLAGS=-lGL -lpng

SRCS=renderer.c texture.c gl_renderer.c sprite.c font.c bullets.c
OBJS=$(SRCS:.c=.o)

%.d:%.c
	@set -e; \
	rm -f $@; \
	$(CC) -MM $(CFALGS) $< > $@.tmp; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.tmp > $@; \
	rm -f $@.tmp; 

all: renderermodule.so

renderermodule.so: $(OBJS)
	gcc -o renderermodule.so -shared $(OBJS) $(LDFLAGS)

clean:
	@echo CLEAN
	@-rm -f *.d
	@-rm -f *.o
	@-rm -f *.so

include $(SRCS:.c=.d)

