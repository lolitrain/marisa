from vector import *
import timer
import video

class SimpleBullet:
    def __init__(self, sprite, start, headto, speed):
        self.sprite = sprite
        self.current_pos = vector(start)
        self.velocity = (vector(headto)-self.current_pos).normalize()*speed
        self.active = True

    def do_frame(self):
        self.current_pos = self.current_pos + self.velocity*timer.frame_time
        
    def draw(self):
        self.sprite.draw(self.current_pos)

    def do_collision(self):
        self.active = False


active_bullets = []

def init():
    video.add_draw_hook(draw)

def add_bullet(bullet):
    active_bullets.append(bullet)

def bullet_count():
    return len(active_bullets)

def do_frame():
    global active_bullets
    for bullet in active_bullets:
        bullet.do_frame()

        if bullet.current_pos[0] > 800 or bullet.current_pos[0] < 0 or \
                bullet.current_pos[1] > 600 or bullet.current_pos[1] < 0:
            bullet.do_collision()
        
    
    active_bullets = [x for x in active_bullets if x.active]

def draw():
    for bullet in active_bullets:
        bullet.draw()
