#!/usr/bin/python
import sys
import pygame
from pygame.locals import *
import config
import video
from testscript import TestStage
import timer
import scriptmanager
import bulletmanager

def quit():
    video.shutdown()
    pygame.quit()
    config.save("config.cfg")
    sys.exit(0)

config.read("config.cfg")
config.read("autoexec.cfg")
pygame.init()
video.init()
timer.init()
scriptmanager.init()
bulletmanager.init()

scriptmanager.add_script(TestStage())
while True:
    timer.tick(60)
    event = pygame.event.poll()
    if event.type == QUIT:
        quit()

    scriptmanager.do_frame()
    bulletmanager.do_frame()
    video.do_frame()

