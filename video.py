import pygame
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.arrays import vbo
import numpy as np
import textures
import random

def init():
  pygame.display.set_mode((800, 600), pygame.DOUBLEBUF|pygame.OPENGL, 24)
  
  glClearColor(random.random(), random.random(), random.random(), 0)
  glEnable(GL_TEXTURE_2D)
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY)

  glViewport(0,0, 800, 600)
  glMatrixMode(GL_PROJECTION)
  glLoadIdentity()
  gluOrtho2D(0, 800, 0, 600)
  glMatrixMode(GL_MODELVIEW)

  glEnable(GL_BLEND)
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
  

binded_textures = {}
current_texture = -1

def bind(texture):
  if texture not in binded_textures:
    binded_textures[texture] = ([], [])

  global current_texture  
  current_texture = texture

def vertex(vertex, tex):
  vertex_array = binded_textures[current_texture][0]
  tex_array = binded_textures[current_texture][1]
  
  vertex_array.append(vertex)
  tex_array.append(tex)

def shutdown():
  textures.clear()

def do_frame():
  global vb
  global tb

  global draw_hooks
  for hook in draw_hooks:
    hook()

  glClear(GL_COLOR_BUFFER_BIT)


  glLoadIdentity()
  global binded_textures
  for texture in binded_textures.iterkeys():
    quads = len(binded_textures[texture][0])
    vertex_array = vbo.VBO(np.array(binded_textures[texture][0], 'f'))
    tex_array = vbo.VBO(np.array(binded_textures[texture][1], 'f'))

    glBindTexture(GL_TEXTURE_2D, texture)

    vertex_array.bind()
    glVertexPointerf(vertex_array)
    tex_array.bind()
    glTexCoordPointerf(tex_array)
    glDrawArrays(GL_QUADS, 0, quads)
    vertex_array.unbind()
    tex_array.unbind()

  binded_textures = {}

  pygame.display.flip()


draw_hooks = []
def add_draw_hook(hook):
  draw_hooks.append(hook)


