import pygame
from settings import *
from bullet import Bala

class Player(pygame.sprite.Sprite):
    def __init__(self, x, y, width, height, ammo, hp, group):
        super().__init__(group)
        self.name = "Player"
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.direction = pygame.math.Vector2()
        self.player_idle = [player_idle_1, player_idle_2,player_idle_3, player_idle_4, player_idle_5]
        self.player_walk = [player_walk_1, player_walk_2, player_walk_3,player_walk_4, player_walk_5, player_walk_6]
        self.player_idle_index = 0
        self.player_walk_index = 0 
        self.image = self.player_idle[self.player_idle_index]
        self.rect = self.image.get_rect(center=(self.x, self.y))
        self.life = hp
        self.target_life = hp
        self.life_bar_lar = hp
        self.life_ratio = self.target_life / self.life_bar_lar
        self.life_change_speed = 3
        self.points = 0
        self.speed = 10
        self.isMoving = False
        self.group = group
        self.last_shoot = pygame.time.get_ticks()
        self.ammo = ammo
        self.start_ammo = ammo
        self.isDead = False
        self.mask = pygame.mask.from_surface(self.image)
        self.last_created = pygame.time.get_ticks()
    
    

    def Movement(self):
        self.x = self.rect.centerx
        self.y = self.rect.centery
        keys = pygame.key.get_pressed()

        if keys[pygame.K_a] and self.rect.left > 0:
            self.direction.x = -1 * self.speed

        elif keys[pygame.K_d] and self.rect.right < bg_size[0]:
            self.direction.x = 1 * self.speed
        else:
            self.direction.x = 0

        if keys[pygame.K_w] and self.rect.top > 0:
            self.direction.y = -1 * self.speed

        elif keys[pygame.K_s] and self.rect.bottom < bg_size[1]:
            self.direction.y = 1 * self.speed

        else:
            self.direction.y = 0

        self.rect.centerx += self.direction.x
        self.rect.centery += self.direction.y
        

    # esse metodo desenha o player na tela
    #animação do player, de idle e andando.
    def animate_player(self):
        mouseX, mouseY = pygame.mouse.get_pos()
        # animação do player
        self.player_idle_index += 0.2
        self.player_walk_index += 0.2
        # caso o index fique igual ao tamanho da lista, ele resetad
        if self.player_idle_index >= len(self.player_idle):
            self.player_idle_index = 0
 
        if self.player_walk_index >= len(self.player_walk):
            self.player_walk_index = 0   

        if self.direction.x == 0 and self.direction.y == 0:
            player_walk_index = 0
            if self.x > mouseX:
                pygame.transform.flip(self.player_idle[int(self.player_idle_index)], True, False)
            else:
                pygame.transform.flip(self.player_idle[int(self.player_idle_index)], False, False)
        else:
            player_idle_index = 0
            if self.x > mouseX:
                self.image = pygame.transform.flip(self.player_walk[int(self.player_walk_index)], True, False)
            else:
                self.image = pygame.transform.flip(self.player_walk[int(self.player_walk_index)], False, False)
        
        return self.image    

    def updatelife(self):
        self.criarvida()

    def tomardano(self, amount):
        if self.target_life > 0:
            self.target_life -= amount
        if self.target_life <= 0:
            self.target_life = 0

    def criarvida(self):

        if self.life < self.target_life:
            self.life += self.life_change_speed
        
        if self.life > self.target_life:
            self.life -= self.life_change_speed

        life_rect = pygame.Rect(10, 25, self.life/self.life_ratio, 25)

        pygame.draw.rect(screen, (79, 79, 79), (10, 25, self.life_bar_lar, 25))
        pygame.draw.rect(screen, (178, 34, 34), life_rect)
        pygame.draw.rect(screen, (54, 54, 54),(10, 25, self.life_bar_lar, 25), 4)
        

    def atirar(self, mouseX, mouseY):
        cooldown = 120
        agora = pygame.time.get_ticks()

        if pygame.mouse.get_pressed()[0]:
            clicking = True
        else:
            clicking = False

        if clicking and self.ammo > 0 and agora - self.last_shoot > cooldown:
            bullet = Bala(self.rect.centerx - self.group[1].offset.x, self.rect.centery - self.group[1].offset.y, mouseX, mouseY, bullet_group)
            self.last_shoot = agora 
            self.ammo -= 1
        
    def collision(self):
        mage_bullet_collision = pygame.sprite.spritecollide(self, mage_bullet_group, True, pygame.sprite.collide_mask) 

        if mage_bullet_collision:
            self.tomardano(5) 
          

        enemy_collision = pygame.sprite.spritecollide(self, enemy_group, False, pygame.sprite.collide_mask)

        if enemy_collision:
            self.tomardano(2)


             
    def update(self):
        self.collision()
        self.Movement()
        self.animate_player()
    
 
