CFLAGS=-Wall -I/usr/include/python2.7
LDFLAGS=-lGL -lpng

OBJS=renderer.o texture.o gl_renderer.o sprite.o font.o bullets.o

all: renderermodule.so

renderermodule.so: $(OBJS)
	gcc -o renderermodule.so -shared $(OBJS) $(LDFLAGS)

clean:
	-rm *.o
	-rm *.so