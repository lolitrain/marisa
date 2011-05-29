import textures
import sprite
from vector import vector

# Represents a moving entity
class Entity:
    def __init__(self, sprite):
        self.sprite = sprite
        self.initial_pos = vector((100, 800))
        self.final_pos = vector((550, 0))
        self.current_pos = self.initial_pos
        self.velocity = (self.final_pos-self.initial_pos).normalize()*0.5
        self.path_length = (self.final_pos - self.initial_pos).length()

    def do_frame(self, t):
        self.current_pos = self.current_pos + self.velocity*t
        travel_distance = (self.current_pos - self.initial_pos).length()
        if(travel_distance > self.path_length):
            self.current_pos = self.initial_pos

    def draw(self):
        self.sprite.draw(self.current_pos)
