import pygame
from OpenGL.GL import *
from OpenGL.GLU import *
import config
import random
import textures
import sprite
import console

draw_hooks = []

binded_textures = {}
current_texture = -1

def bind_texture(texture):
  if texture not in binded_textures:
    binded_textures[texture] = ([], [])

  global current_texture  
  current_texture = texture

def vertex(vertex, tex):
  vertex_array = binded_textures[current_texture][0]
  tex_array = binded_textures[current_texture][1]

  vertex_array.append(vertex)
  tex_array.append(tex)

def draw ():
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
  glMatrixMode(GL_MODELVIEW)
  glLoadIdentity()

  for hook in draw_hooks:
    hook()
    
  global binded_textures
  for texture in binded_textures.iterkeys():
    vertex_array = binded_textures[texture][0]
    tex_array = binded_textures[texture][1]

    glBindTexture(GL_TEXTURE_2D, texture)
    glBegin(GL_QUADS)
    for vertex, tex in zip(vertex_array, tex_array):
      glTexCoord(tex[0], tex[1])
      glVertex(vertex[0], vertex[1])
    glEnd()

  binded_textures = {}
  
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
