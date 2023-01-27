import pygame
from settings import *
from bullet import Bala
from explosion import Explosion

class Enemy(pygame.sprite.Sprite):
    def __init__(self, x, y, width, height, group, mult):
        super().__init__(group)
        self.name = "enemy"
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.image = pygame.image.load("sprites/ArteDoJogo/caveiraChamas.png").convert_alpha()
        self.rect = self.image.get_rect(center=(self.x, self.y))
        self.life = 1 + enemy_mult
        self.speed = 3
        self.animation_index = 0
        self.isDead = False
        self.group = group
        self.mask = pygame.mask.from_surface(self.image)
        self.mult = mult
        
    #movimentação do enemy.
    def movimentoEnemy(self):
        for player in player_group.sprites():
            if self.rect.centerx > player.x:
                self.rect.centerx -= self.speed

            if self.rect.centerx < player.x:
                self.rect.centerx += self.speed

            if self.rect.centery > player.y:
                self.rect.centery -= self.speed

            if self.rect.centery < player.y:
                self.rect.centery += self.speed

            

    #o metodo update vai verificar se o tiro do player entrou em colisão com o enemy, e se entrou
    # o enemy vai perder uma vida. 
    def update(self):
        self.movimentoEnemy()


    def kill_enemy(self, player, insta_kill):
        self.play_explosion()
        death = Explosion(self.rect.centerx, self.rect.centery, 32, 32, self.group[1])
        player.points += 1 * self.mult
        self.kill()

        if insta_kill:
            self.life = 1


                    

    def play_explosion(self):
         explosion_sound.play()