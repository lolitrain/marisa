import pygame

current_time = 0
frame_time = 0
def init():
    current_time = pygame.time.get_ticks()

def tick(framerate):
    global current_time
    global frame_time
    total_wait = int(1000/framerate)
    passed_time = pygame.time.get_ticks() - current_time
    wait = total_wait-passed_time
    if wait > 0:
        pygame.time.wait(wait)
    frame_time = pygame.time.get_ticks() - current_time
    current_time = pygame.time.get_ticks()
    return passed_time

def gettime():
    return current_time

def fps():
    return 1000.0/frame_time

# Script utility function
# waits a certain number of milliseconds
def wait(msec):
    start = gettime()
    current_time = gettime()
    while current_time - start < msec:
        yield
        current_time = gettime()



