from vector import *
import video
import renderer
from math import sin, cos, radians

def init():
    video.add_draw_hook(renderer.bullets_draw)

def shutdown():
    renderer.bullets_shutdown()

def add_bullet(sprite, start, headto, speed):
    renderer.bullet_create(sprite.sprite, start, headto, speed)

def add_bullet_angle(sprite, start, angle, speed):
    headto = (start[0]+cos(radians(angle))*speed, start[1]+sin(radians(angle))*speed)
    renderer.bullet_create(sprite.sprite, start, headto, speed)

def bullet_count():
    return renderer.bullets_count()

def do_frame():
    renderer.bullets_do_frame()

