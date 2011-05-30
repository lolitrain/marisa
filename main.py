#!/usr/bin/python
import sys
import pygame
from pygame.locals import *
import config
import video
from testscript import TestScript
import timer

def quit():
    video.shutdown()
    pygame.quit()
    config.save("config.cfg")
    sys.exit(0)

config.read("config.cfg")
config.read("autoexec.cfg")
pygame.init()
video.init()
testscript = TestScript()

timer.init()
while True:
    timer.tick(60)
    event = pygame.event.poll()
    if event.type == QUIT:
        quit()

    testscript.do_frame()
    video.do_frame()

