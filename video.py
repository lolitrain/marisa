import pygame
import textures
import renderer

def init():
  pygame.display.set_mode((800, 600), pygame.DOUBLEBUF|pygame.OPENGL, 24)
  renderer.init()

def shutdown():
  textures.clear()

def do_frame():
  global draw_hooks
  for hook in draw_hooks:
    hook()

  renderer.do_frame()

  pygame.display.flip()


draw_hooks = []
def add_draw_hook(hook):
  draw_hooks.append(hook)


