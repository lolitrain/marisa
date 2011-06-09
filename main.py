#!/usr/bin/python
import OpenGL
OpenGL.ERROR_CHECKING=False
import sys
import pygame
from pygame.locals import *
import config
import video
from demo import DemoStage
from testscript import TestStage
import timer
import scriptmanager
import bulletmanager
import console
import inputmanager

def quit():
    bulletmanager.shutdown()
    scriptmanager.shutdown()
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
inputmanager.init()

inputmanager.bind(K_ESCAPE, lambda x: quit())
scriptmanager.add_script(console.Console())
main_script = TestStage()

while True:
    timer.tick(60)
    event = pygame.event.poll()
    if event.type == QUIT:
        quit()
    elif event.type != NOEVENT:
        inputmanager.handle(event)

    scriptmanager.do_frame()
    bulletmanager.do_frame()
    video.do_frame()

