import pygame
import math
from settings import *
class MageBullet(pygame.sprite.Sprite):
    def __init__(self, x, y, width, height, angle, group):
        super().__init__(group)
        self.name = "mage_bullet"
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.speed = 10
        self.animation = [projetilMago_0,projetilMago_1,projetilMago_2,projetilMago_3,projetilMago_4]
        self.index = 0 
        self.image = self.animation[self.index]
        self.angle = angle
        self.velX = math.cos(self.angle) * self.speed
        self.velY = math.sin(self.angle) * self.speed
        self.rect = self.image.get_rect(center = (self.x, self.y))
        self.mask = pygame.mask.from_surface(self.image)

    def animate(self):
        self.index += 0.1

        if self.index > len(self.animation):
            self.index = 0 

        self.image = self.animation[int(self.index)]

    def update(self):
        self.animate()
        self.x -= int(self.velX)
        self.y -= int(self.velY)
        self.rect.center = (self.x, self.y)

        if self.rect.left < 0:
            self.kill()
            
        elif self.rect.right > bg_size[0]:

            self.kill()

        if self.rect.bottom < 0:

            self.kill()

        elif self.rect.top > bg_size[1]:

            self.kill()

    


  
        
