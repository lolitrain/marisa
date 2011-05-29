#!/usr/bin/python
import sys
import pygame
from pygame.locals import *
import config
import video
from entity import Entity
import textures
from sprite import Sprite

def quit():
    video.shutdown()
    pygame.quit()
    config.save("config.cfg")
    sys.exit(0)

config.read("config.cfg")
config.read("autoexec.cfg")
pygame.init()
video.init()

smile_sprite = Sprite(textures.get("smile"), (64,64))
smile_bullet = Entity(smile_sprite)
video.add_entity(smile_bullet)

clock = pygame.time.Clock()
time = clock.tick(60)
while True:
    time = clock.tick(60)
    event = pygame.event.poll()
    if event.type == QUIT:
        quit()

    smile_bullet.do_frame(time)
    video.do_frame()

