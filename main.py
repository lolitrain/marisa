#!/usr/bin/python
import sys
import pygame
from pygame.locals import *
import config
import video


def quit():
    video.shutdown()
    pygame.quit()
    config.save("config.cfg")
    sys.exit(0)

config.read("config.cfg")
config.read("autoexec.cfg")
pygame.init()
video.init()
while True:
    event = pygame.event.poll()
    if event:
        if event.type == QUIT:
            quit()
    video.do_frame()

