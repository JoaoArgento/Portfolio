import pygame
import math
from settings import *

class Bala(pygame.sprite.Sprite):
    def __init__(self, x, y, mouseX, mouseY, group):
        super().__init__(group)
        self.name = "bullet"
        self.x = x
        self.y = y
        self.mouseX = mouseX
        self.mouseY = mouseY
        self.speed = 20
        self.angle = math.atan2(y - mouseY, x - mouseX) 
        self.velX = math.cos(self.angle) * self.speed
        self.velY = math.sin(self.angle) * self.speed
        self.image = pygame.transform.scale((pygame.image.load("sprites/ArteDoJogo/balaRaio0.png").convert_alpha()), (16, 16))
        self.rect = self.image.get_rect(center=(x, y))
        self.mask = pygame.mask.from_surface(self.image)     

    def update(self):
        # mudando o x  e  o y dela de acordo com a velocity dela.
        self.rect.centerx -= int(self.velX)
        self.rect.centery -= int(self.velY)

        if self.rect.left < 0:
            self.kill()
            
        elif self.rect.right > bg_size[0]:

            self.kill()

        if self.rect.bottom < 0:

            self.kill()

        elif self.rect.top > bg_size[1]:

            self.kill()


 