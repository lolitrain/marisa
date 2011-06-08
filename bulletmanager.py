from vector import *
import video
import renderer

# class SimpleBullet:
#     def __init__(self, sprite, start, headto, speed):
#         self.sprite = sprite
#         self.current_pos = vector(start)
#         self.velocity = (vector(headto)-self.current_pos).normalize()*speed
#         self.active = True

#     def do_frame(self):
#         self.current_pos = self.current_pos + self.velocity*timer.frame_time
        
#     def draw(self):
#         self.sprite.draw(self.current_pos)

#     def do_collision(self):
#         self.active = False


def init():
    video.add_draw_hook(renderer.bullets_draw)

def shutdown():
    renderer.bullets_shutdown()

def add_bullet(sprite, start, headto, speed):
    renderer.bullet_create(sprite.sprite, start, headto, speed);

def bullet_count():
    return renderer.bullets_count()

def do_frame():
    renderer.bullets_do_frame()

