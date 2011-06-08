import pygame
from pygame.locals import *

def init():
    pygame.event.set_allowed(None)
    pygame.event.set_allowed((QUIT, KEYDOWN, KEYUP))

    global action_map
    action_map = {}

def handle(event):

    if event.type == NOEVENT:
        return

    global action_map
    if event.key not in action_map:
        return

    action_map[event.key](event.type == KEYDOWN)

def bind(key, action):
    global action_map

    action_map[key] = action
