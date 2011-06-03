import pygame
from OpenGL.GL import *
from OpenGL.GLU import *
import config
import random
import textures
import sprite
import console

draw_hooks = []

def draw ():
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
  glMatrixMode(GL_MODELVIEW)
  glLoadIdentity()

  for hook in draw_hooks:
    hook()
  
  glFlush()
  pygame.display.flip()

def init_opengl():
  glShadeModel(GL_SMOOTH)
  glClearColor(random.random(), random.random(), random.random(), 0)
  glClearDepth(1);
#  glEnable(GL_DEPTH_TEST)
#  glDepthFunc(GL_LEQUAL)

  glViewport(0, 0, 800, 600)
  glMatrixMode(GL_PROJECTION)
  glLoadIdentity()
  gluOrtho2D(0, 800, 0, 600)
  glMatrixMode(GL_MODELVIEW)

  glEnable(GL_TEXTURE_2D)
  glEnable(GL_BLEND)
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)

  
def init():
  pygame.display.set_mode((config.getint("video", "width"),config.getint("video", "height")), pygame.DOUBLEBUF|pygame.OPENGL, 24)
  init_opengl()
  console.write("Initializing video")
  
def shutdown():
  textures.clear()

def do_frame():
  draw()

def add_draw_hook(func):
  draw_hooks.append(func)
