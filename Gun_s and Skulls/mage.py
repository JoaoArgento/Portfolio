import pygame 
from settings import *
from magebullet import MageBullet
from explosion import Explosion

class Mage(pygame.sprite.Sprite):
    def __init__(self, x, y, width, height, group, mult):
        super().__init__(group)
        self.name = "Mage"
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.idle_animation = [mage_idle_1,mage_idle_2,mage_idle_3,mage_idle_4,mage_idle_5]
        self.atk_animation = [mage_atk_1,mage_atk_2,mage_atk_3,mage_atk_4]
        self.animation_idle_index = 0
        self.animation_atk_index = 0
        self.image = self.idle_animation[self.animation_idle_index]
        self.rect = self.image.get_rect(center = (self.x, self.y))
        self.life_mage = 3 + enemy_mult
        self.isAttacking = False
        self.mask = pygame.mask.from_surface(self.image)
        self.group = group
        self.mult = mult  

    def animation_mage(self):
        self.animation_idle_index += 0.1
        self.animation_atk_index += 0.1

        if self.animation_idle_index > len(self.idle_animation):
             self.animation_idle_index = 0

        elif self.animation_atk_index > len(self.atk_animation):
            self.animation_atk_index = 0

        if not self.isAttacking:
            self.animation_atk_index = 0
            self.image = self.idle_animation[int(self.animation_idle_index)]
        else:
            self.animation_idle_index = 0
            self.image = self.atk_animation[int(self.animation_atk_index)]



    def update(self):
        self.animation_mage()

    def kill_mage(self,player, insta_kill):
        explosion_sound.play() 
        death = Explosion(self.x, self.y, 32, 32, self.group[1])
        player.points += 1 * self.mult
        self.kill()


        if insta_kill:
            self.life_mage = 1
                

    def atirar(self, mage_shooting_count, bullet_angle, camera_group):
        for mage in mage_group:
            for x in range(0, 15):
                mage_bullet = MageBullet(mage.x, mage.y, 16, 16, bullet_angle, [mage_bullet_group, camera_group])
                bullet_angle -= 75
                mage_bullet_group.add(mage_bullet)    