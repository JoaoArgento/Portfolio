import pygame
from settings import *


class Boss(pygame.sprite.Sprite):
    def __init__(self, x, y, width, height, group):
        super().__init__()
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.walk_animation = [boss_walk_1,boss_walk_2,boss_walk_3]
        self.atk_animation = [boss_atk_1,boss_atk_2,boss_atk_3,boss_atk_4,boss_atk_5]
        self.walk_index = 0
        self.atk_index = 0 
        self.image = self.walk_animation[self.walk_index]
        self.rect = self.image.get_rect(center = (self.x, self.y))
        self.life = 50
        self.speed = 3
        self.isAtk = False
        self.isWalking = True

    def animate(self):
        self.walk_index += 0.1
        self.atk_index += 0.1

        if self.walk_index > len(self.walk_animation):
            self.walk_index = 0
        elif self.atk_index > len(self.atk_animation):
            self.atk_index = 0

        if not self.isWalking:
            self.walk_index = 0
            self.image = self.atk_animation[int(self.atk_index)]

        else:
            self.atk_index = 0 
            self.image = self.walk_animation[int(self.walk_index)]



    def movimentoBoss(self, player):
        if not pygame.sprite.collide_rect(player, self):
            if self.atk_index == 0:
                self.isWalking = True
                self.isAtk = False

            if self.isWalking and not self.isAtk:
                if self.x > player.x:
                    self.x -= self.speed

                if self.x < player.x:
                    self.x += self.speed

                if self.y > player.y:
                    self.y -= self.speed

                if self.y < player.y:
                    self.y += self.speed
        else:
            self.isWalking = False
            self.isAtk = True
            if self.atk_index > 1:
                player.tomardano(15)

        self.rect.center = (self.x, self.y)
        

    def bosslife(self, isAlive):
        boss_collision = pygame.sprite.spritecollide(self, bullet_group,True)
        if boss_collision:
            self.life -= 1

    def kill_boss(self):
        if self.life <= 0: 
            isAlive = False 
            self.kill()
            
    def update(self, isAlive, player):
        self.animate()
        self.bosslife(isAlive)
        self.movimentoBoss(player)
        self.kill_boss()
