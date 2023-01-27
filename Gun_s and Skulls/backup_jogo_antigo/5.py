import pygame
import pygame.mixer
import sys
import math
from pygame.locals import *
from random import randint
from settings import *

pygame.init()

pygame.display.set_caption("grande dia")
#icon = pygame.image.load("").convert_alpha()
# pygame.display.set_icon(icon)

#pygame.mouse.set_visible(False)

# timer do enemy
timer_event = pygame.USEREVENT + 1
enemy_spawn = int(randint(10000, 20000)//100)
pygame.time.set_timer(timer_event, enemy_spawn)
enemy_count = 20

# timer do double xp
timer_item_event = pygame.USEREVENT + 2
creating_item = int(randint(10000, 20000)//100)
pygame.time.set_timer(timer_item_event, creating_item)
item_count = randint(120, 200)
duration_double = 600
insta_duration = 600
double_xp = False

# mudando de round
round_timer_event = pygame.USEREVENT + 3
round_change = 3000//100
pygame.time.set_timer(round_timer_event, round_change)
round_count = 60
turn_round = True

#timer do tiro, evita de ficar atirando muito rapido
clicking_event = pygame.USEREVENT + 4
clicking_timer = 150
pygame.time.set_timer(clicking_event,clicking_timer)
clicking_count = 1

#timer do tiro do mage.
mage_shooting_event = pygame.USEREVENT + 5
mage_shooting_timer = 3000//100
pygame.time.set_timer(mage_shooting_event, mage_shooting_timer)
mage_shooting_count = 60

# sons
max_ammo_sound = pygame.mixer.Sound("sons/maxammo.wav")
double_points_sound = pygame.mixer.Sound("sons/doublepoints.wav")
insta_kill_sound = pygame.mixer.Sound("sons/instakill.wav")
ka_boom_sound = pygame.mixer.Sound("sons/kabom.wav")

# sistema de pontos
font = pygame.font.Font('font/Pixeltype.ttf', 50)
round_font = pygame.font.Font('font/Pixeltype.ttf', 128)



# munição
start_ammo = 70
ammo = 30
double_points = False

# criando os botoes do jogo
class Button(pygame.sprite.Sprite):
    def __init__(self, x, y):
        super().__init__()
        self.x = x
        self.y = y
        self.image = pygame.Surface((128,128))
        self.image.fill((255,0,0))
        self.rect = self.image.get_rect(center = (self.x, self.y))
        
    
    def desenhar_button(self, screen):
        screen.blit(self.image,self.rect)
        self.detectar_clicker()

    def detectar_clicker(self):
        global menu, game_state
        if pygame.mouse.get_pressed()[0]:
            if button_play.rect.collidepoint(mouseX, mouseY):
                menu = False
                game_state = True
            elif button_quit.rect.collidepoint(mouseX, mouseY):
                pygame.quit()
                sys.exit()

class Ponteiro(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = pygame.image.load("sprites/crosshair.png").convert_alpha()
        self.rect = self.image.get_rect()

    def update(self):
        self.rect.center = pygame.mouse.get_pos()

# modelo do player, basicamente  o player vai ser criado a partir dessa classe.
class Player(pygame.sprite.Sprite):
    def __init__(self, x, y, width, height):
        super().__init__()
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
        self.life = 300
        self.target_life = 300
        self.life_bar_lar = 300
        self.life_ratio = self.target_life / self.life_bar_lar
        self.life_change_speed = 3
        self.points = 0
        self.speed = 10
        self.isMoving = False

    def Movement(self):
        if keys[pygame.K_a] and self.x > 0 + self.width:
            self.direction.x =  -1 * self.speed
           
        elif keys[pygame.K_d] and self.x < largura + self.width:
            self.direction.x = 1 * self.speed
        else:
            self.direction.x = 0

        if keys[pygame.K_w] and self.y > 0 + self.height:
            self.direction.y = -1 * self.speed

        elif keys[pygame.K_s] and self.y < altura - self.height:
            self.direction.y = 1 * self.speed

        else:
            self.direction.y = 0

        self.rect.centerx += self.direction.x
        self.rect.centery += self.direction.y
        self.x = self.rect.centerx
        self.y = self.rect.centery
    # esse metodo desenha o player na tela
    #animação do player, de idle e andando.
    def desenhoplayer(self, screen):
        self.Movement()
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
                screen.blit(pygame.transform.flip(self.player_idle[int(self.player_idle_index)], True, False), self.rect)
            else:
                screen.blit(pygame.transform.flip(self.player_idle[int(self.player_idle_index)], False, False), self.rect)
        else:
            player_idle_index = 0
            if self.x > mouseX:
                screen.blit(pygame.transform.flip(self.player_walk[int(self.player_walk_index)], True, False), self.rect)
            else:
                screen.blit(pygame.transform.flip(self.player_walk[int(self.player_walk_index)], False, False), self.rect)
            

    def updatelife(self):
        self.criarvida()

    def tomardano(self, amount):
        if self.target_life > 0:
            self.target_life -= amount
        if self.target_life <= 0:
            self.target_life = 0

    def criarvida(self):
        transition_width = 0

        if self.life < self.target_life:
            self.life += self.life_change_speed
            transition_width = int((self.target_life - self.life)/self.life_ratio)

        if self.life > self.target_life:
            self.life -= self.life_change_speed
            transition_width = int((self.target_life - self.life)/self.life_ratio)

        life_rect = pygame.Rect(10, 25, self.life/self.life_ratio, 25)

        pygame.draw.rect(screen, (79, 79, 79), (10, 25, self.life_bar_lar, 25))
        pygame.draw.rect(screen, (178, 34, 34), life_rect)
        pygame.draw.rect(screen, (54, 54, 54),(10, 25, self.life_bar_lar, 25), 4)

#adicionando o player em um grupo unico (só tem ele no grupo)
player = Player(400, 300, 32, 32)
player_group = pygame.sprite.GroupSingle()
player_group.add(player)
# modelo da bullet, é a partir dessa class que a bala vai ser criada
class Bala(pygame.sprite.Sprite):
    def __init__(self, x, y, mouseX, mouseY):
        super().__init__()
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

    def update(self):
        # mudando o x  e  o y dela de acordo com a velocity dela.
        self.x -= int(self.velX)
        self.y -= int(self.velY)
        self.rect.center = (self.x, self.y)

    def desenhotiro(self, screen):

        bullet_group.draw(screen)

#todos os itens bonus são criados a partir dessa classe.
class Items(pygame.sprite.Sprite):
    def __init__(self, x, y, width, height):
        super().__init__()
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.image = pygame.Surface((self.width, self.height))
        self.rect = self.image.get_rect(center=(self.x, self.y))

    def desenhomaxammo(self, screen):
        self.image.fill((128, 128, 128))
        max_ammo_group.draw(screen)

    def PlayMusicMaxAmmo(self):
        global ammo
        max_ammo_sound.play(loops= 0)
        max_ammo_sound.set_volume(0.05)
        ammo = start_ammo

    def desenhodoublexp(self, screen):
        self.image.fill((0, 0, 255))
        item_group.draw(screen)

    def PlayMusicDoublexp(self):
        if double_xp:
            double_points_sound.play(loops=0)
            double_points_sound.set_volume(0.05)

    def desenhoinstakill(self, screen):
        self.image.fill((0, 255, 0))
        item_group.draw(screen)

    def PlayMusicInstaKill(self):
        if insta_kill:
            insta_kill_sound.play(loops=0)
            insta_kill_sound.set_volume(0.05)

    def desenhokaboom(self, screen):
        self.image.fill((255, 255, 0))
        item_group.draw(screen)

    def PlayMusicKaboom(self):
        if ka_boom:
            ka_boom_sound.play(loops=0)
            ka_boom_sound.set_volume(0.05)

    def criar_item(self):
        choice_item = randint(1, 3)
        if choice_item == 1:
            item_group.add(doublexp)
            double_xp = True
            duration_double = 600

        elif choice_item == 2:
            item_group.add(instakill)
            draw_insta_kill = True

        elif choice_item == 3:
            item_group.add.add(kabom)
            draw_kaboom = True

    def verificando_colisao(self):
        for sprite in item_group.sprites():
            if sprite.rect.colliderect(player.rect):
                if choice_item == 1:
                    self.PlayMusicDoublexp()
                    double_points = True
                    sprite.remove(doublexp)
                    double_xp = False

                elif choice_item == 2:
                    ka_boom = True
                    self.PlayMusicKaboom()
                    sprite.remove(kabom)
                    draw_kaboom = False
                    enemy.kill()

                elif choice_item == 2:
                    insta_kill = True
                    self.PlayMusicInstaKill()
                    draw_insta_kill = False
                    sprite.remove(instakill)
                    insta_duration = 600
     
        def update(self):
            self.criar_item()
            self.verificando_colisao()
#criando o enemy
class Enemy(pygame.sprite.Sprite):
    def __init__(self, x, y, width, height):
        super().__init__()
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.image = pygame.image.load("sprites/ArteDoJogo/caveiraChamas.png").convert_alpha()
        self.death_animation_list = [enemy_death_1,enemy_death_2,enemy_death_3,enemy_death_4,enemy_death_5, enemy_death_6]
        self.animation_index = 0
        self.death_animation = self.death_animation_list[self.animation_index]
        self.rect = self.image.get_rect(center=(self.x, self.y))
        self.life = 1 + enemy_mult
        self.speed = 3
        self.animation_index = 0
        self.isDead = False

        
    def desenhoEnemy(self, screen):
        enemy_group.draw(screen)
        self.movimentoEnemy()
        self.update()
    
    def animation_enemy(self):
        self.animation_index += 0.1
        if not self.isDead:
            self.animation_index = 0
            self.image = pygame.image.load("sprites/ArteDoJogo/caveiraChamas.png").convert_alpha()
        else:
            self.speed = 0
            if self.animation_index >= len(self.death_animation_list):
                 self.animation_index = 0
    

            self.image = self.death_animation_list[int(self.animation_index)]
    #movimentação do enemy.
    def movimentoEnemy(self):
        enemy_collision = pygame.sprite.collide_rect(player,enemy)
        if enemy_collision and not self.isDead:
             player.tomardano(2)
        else:
            if self.x > player.x:
                self.x -= self.speed

            if self.x < player.x:
                self.x += self.speed

            if self.y > player.y:
                self.y -= self.speed

            if self.y < player.y:
                self.y += self.speed

            self.rect.center = (self.x, self.y)
           

    #o metodo update vai verificar se o tiro do player entrou em colisão com o enemy, e se entrou
    # o enemy vai perder uma vida. 
    def update(self):
        enemy_collision = pygame.sprite.spritecollide(enemy, bullet_group, True)
        if enemy_collision:
            self.life -= 1
        self.kill()
        self.animation_enemy()

    def kill(self):
        global ka_boom, insta_kill, insta_duration
        if self.life <= 0:
            if self.animation_index >= 4:
                enemy_group.remove(enemy)
                player.points += 1 * mult
            self.isDead = True

        elif ka_boom:
            enemy_group.empty()
            ka_boom = False

        elif insta_kill:
            self.life = 1
            insta_duration -= 1
            if insta_duration <= 0:
                insta_kill = False
                                     
#criando o boss
class Boss(pygame.sprite.Sprite):
    def __init__(self, x, y, width, height):
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

    def animation_boss(self):
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



    def movimentoBoss(self):
        if not pygame.sprite.collide_rect(player, boss):
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

        self.rect.center = (self.x, self.y)
        
    def desenhoboss(self, screen):
        self.animation_boss()
        boss_group.draw(screen)

    def bosslife(self, isAlive):
        boss_collision = pygame.sprite.spritecollide(bullet,boss_group,True)
        if boss_collision:
            self.life -= 5 

        if self.life <= 0: 
            isAlive = False 
            boss_group.remove(boss)
            
    def update(self, isAlive):
        self.bosslife(isAlive)
        self.movimentoBoss()

class Mage(pygame.sprite.Sprite):
    def __init__(self, x, y, width, height):
        super().__init__()
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


    def desenho_mage(self, screen):
        self.animation_mage()
        mage_group.draw(screen)
        self.update()

    def update(self): 
        self.rect.center = (self.x, self.y)
        mage_collision = pygame.sprite.spritecollide(mage, bullet_group, True)
        if mage_collision:
            self.life_mage -= 1
        self.kill()

    def kill(self):
        global ka_boom, insta_kill, insta_duration
        if self.life_mage <= 0:
            mage_group.remove(mage)
            player.points += 1 * mult

        elif ka_boom:
            mage_group.empty()
            ka_boom = False

        elif insta_kill:
            self.life_mage = 1
            insta_duration -= 1
            if insta_duration <= 0:
                insta_kill = False

    def atirar(self, mage_shooting_count, bullet_angle):
        for mage in mage_group:
            for x in range(0, 15):
                mage_bullet = MageBullet(mage.x, mage.y, 16, 16, bullet_angle)
                bullet_angle -= 75
                mage_bullet_group.add(mage_bullet)              

class MageBullet(pygame.sprite.Sprite):
    def __init__(self, x, y, width, height, angle):
        super().__init__()
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.speed = 10
        self.image = pygame.Surface((self.width, self.height))
        self.image.fill((0, 0, 0))
        self.angle = angle
        self.velX = math.cos(self.angle) * self.speed
        self.velY = math.sin(self.angle) * self.speed
        self.rect = self.image.get_rect(center = (self.x, self.y))


    def update(self):
        self.x -= int(self.velX)
        self.y -= int(self.velY)
        self.rect = self.image.get_rect(center = (self.x, self.y))

    def desenhoMage_bullet(self, screen):
        mage_bullet_group.draw(screen) 

 
def criar_mage():
    mage = Mage(randint(30, largura - 20), randint(30,altura - 20),64,64)
    mage_group.add(mage) 

def criar_enemy():
    enemy = Enemy(randint(30, largura - 20), randint(30,altura - 20),64,64)
    enemy_group.add(enemy)

# score do jogo
score_surf = font.render(f'Pontos: {player.points}', False, (64, 64, 64))
score_rect = score_surf.get_rect(topleft=(1100, 20))

# quantidade de munição
ammo_surf = font.render(f'Municao: {ammo}', False, (64, 64, 64))
ammo_rect = ammo_surf.get_rect(topleft=(1100, 60))

#round do game
round_surf = round_font.render(f'Round {game_round}', False, (255, 0, 0))
round_rect = round_surf.get_rect(center=(largura//2, altura//2 - 50))

#instanicando os objetos.
boss = Boss(randint(10, largura - 200), randint(20, altura - 100), 64, 64)
doublexp = Items(randint(10, largura - 100), randint(20, altura - 100), 32, 32)
maxammo = Items(randint(10, largura - 100), randint(20, altura - 100), 32, 32)
instakill = Items(randint(10, largura - 100),randint(20, altura - 100), 32, 32)
kabom = Items(randint(10, largura - 100), randint(20, altura - 100), 32, 32)

#variaveis de controle.
mult = 1
enemy_mult = 1
points_tracker = 5
mage_bullet_angle = 45
anim_count = False

#groups dos objetos.
ponteiro = Ponteiro()
ponteiro_group = pygame.sprite.Group()
ponteiro_group.add(ponteiro)
bullet_group = pygame.sprite.Group()
enemy_group = pygame.sprite.Group()
mage_group = pygame.sprite.Group()
mage_bullet_group = pygame.sprite.Group()

# grupo dos itens
item_group = pygame.sprite.Group()
boss_group = pygame.sprite.Group()
max_ammo_group = pygame.sprite.Group()

#variaveis auxiliares.
running = True
clicking = False
boss_is_alive = False 
menu = True
boss_timer = 150
mage_shooting = False

#criando os buttons.
button_play = Button(largura/2, altura/2)
button_quit = Button(largura/2, altura/2 + 200)

choice_enemy = randint(1,2)
# loop do game
while running:
    while menu:

        screen.fill((0,0,0))
        mouseX, mouseY = pygame.mouse.get_pos()
        

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
                       
        button_play.desenhar_button(screen)
        button_quit.desenhar_button(screen)
        pygame.display.flip()
        clock.tick(60)

    #loop do jogo em si, depois de entrar no menu
    while game_state:
       
        pygame.mouse.set_visible(False)

        #esse é o if responsavel por mudar de round.
        if player.points >= points_tracker and game_round <= 3:
            points_tracker += 5
            turn_round = True
            enemy_mult += 1
            game_round += 1
            round_surf = round_font.render(f'Round {game_round}', False, (255, 0, 0))

            if game_round >= 4:
                turn_round = False      
        
        screen.fill((255, 255, 255)) 

        # atualizando o sistema de pontos

        ammo_surf = font.render(f'Municao: {ammo}', False, (64,64,64))
        score_surf = font.render(f'Pontos: {player.points}', False, (64,64,64))

        # atribuindo a posição do mouse para as duas variaveis
        mouseX, mouseY = pygame.mouse.get_pos()
    
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            
            elif event.type == mage_shooting_event and len(mage_group) > 0:
                mage_shooting_count -= 1
               
    
            elif event.type == boss_timer:
                boss_timer -= 1 

            elif event.type == timer_event:

                enemy_count -= 1
                
            elif event.type == clicking_event:

                clicking_count = 0

                # criando os itens (exceto o max ammo)
            elif event.type == timer_item_event and not(draw_insta_kill) and not(draw_kaboom) and not(double_xp):
                item_count -= 1

                # mudando de round
            elif event.type == round_timer_event and turn_round:

                round_count -= 1

            elif event.type ==  MOUSEBUTTONDOWN: 
                if event.button == 1:
                    clicking = True
            
            elif event.type == MOUSEBUTTONUP:

                 clicking = False
                
            #programação do tiro.    
            if clicking and ammo > 0 and clicking_count == 0:
                bullet = Bala(player.rect.centerx, player.rect.centery, mouseX, mouseY)
                bullet_group.add(bullet)
                ammo -= 1
                clicking_count = 1


            keys = pygame.key.get_pressed()

        # logica dos timers
        if game_round >= 1 and game_round <= 3:
            if item_count <= 0:
                item_group.update()
                item_count = randint(120, 200)
                        
            if round_count <= 0:
                turn_round = False
                round_count = 60
            
            if game_round == 1:
                if enemy_count <= 0 and len(mage_group) <= 4:
                    criar_mage()
                    enemy_count = 20

            if mage_shooting_count <= 0:
                mage.atirar(mage_shooting_count, mage_bullet_angle)
                mage_shooting_count = 100
                    
            if game_round == 2:

                if enemy_count <= 0:

                    choice_enemy = randint(1,2)

                    if choice_enemy == 1:                   
                        criar_mage()

                    elif choice_enemy == 2:
                        criar_enemy()

                    enemy_count = 20
        

        else:
            boss_surf = font.render(f'O brabo foi criado...', False, (64, 64, 64))
            boss_rect = ammo_surf.get_rect(center = (largura//2, altura//2))
            if boss_timer > 0:
                screen.blit(boss_surf,boss_rect)
                boss_timer -= 1 
            else:
                boss_timer = 0 
                boss_is_alive = True
                
            if boss_is_alive:   
                boss_group.add(boss)

                for boss in boss_group:
                    boss.desenhoboss(screen)
                    boss.update(boss_is_alive)
           
        # colisoes dos items
        if ammo == 0:
            max_ammo_group.add(maxammo)

            for item in max_ammo_group:
                item.desenhomaxammo(screen)

        max_collision = pygame.sprite.spritecollide(player, max_ammo_group, True)

        if max_collision:
            max_ammo_group.remove(maxammo)
            maxammo.PlayMusicMaxAmmo()

            # ganhando o doubleXP

        if double_xp:
                # mantendo o double na tela caso double_xp for igual a rue
            for item in item_group:
                item.desenhodoublexp(screen)
                # quando a duração do double for 0, vai tirar o double.

        elif draw_insta_kill:
            for item in item_group:
                    item.desenhoinstakill(screen)

        elif draw_kaboom:
            for item in item_group:
                    item.desenhokaboom(screen)

        #colisão dos itens.
        #insta_collision = pygame.sprite.spritecollide(player, insta_kill_group, True)
        #double_collision = pygame.sprite.spritecollide(player, double_point_group, True)
        #kaboom_collision = pygame.sprite.spritecollide(player, ka_boom_group, True)

        if double_points:
            mult = 2
            duration_double -= 1

        else:
            mult = 1

        if duration_double <= 0:
            double_points = False
        
        keys = pygame.key.get_pressed()
            # movimentação do player

        player.desenhoplayer(screen)
        player.updatelife()

        for mBullet in mage_bullet_group:
            mBullet.desenhoMage_bullet(screen)

            if mBullet.rect.x < 0:
                mage_bullet_group.remove(mBullet)

            elif mBullet.rect.x > largura:
                mage_bullet_group.remove(mBullet)

            if mBullet.rect.y < 0:
                    mage_bullet_group.remove(mBullet)

            elif mBullet.rect.y > altura:
                    mage_bullet_group.remove(mBullet)

            mage_bullet_collision = pygame.sprite.collide_rect(mBullet, player)

            if mage_bullet_collision:
                mage_bullet_group.remove(mBullet)
                player.tomardano(5)
           
        for enemy in enemy_group:
            enemy.desenhoEnemy(screen)
    
        
        for mage in mage_group:
            mage.desenho_mage(screen)

            # mantendo os tiros na tela
        for bullet in bullet_group:
            bullet.desenhotiro(screen)

            if bullet.rect.x < 0:
                bullet_group.remove(bullet)

            elif bullet.rect.x > largura:
                bullet_group.remove(bullet)

            if bullet.rect.y < 0:
                bullet_group.remove(bullet)

            elif bullet.rect.y > altura:
                bullet_group.remove(bullet)

            # mantendo o enemy na tela d

        ponteiro_group.draw(screen)
        ponteiro_group.update()
        screen.blit(ammo_surf, ammo_rect)

        if turn_round:
            screen.blit(round_surf, round_rect)

        mage_bullet_group.update()
        bullet_group.update()
        screen.blit(score_surf, score_rect)
        pygame.display.flip()
        clock.tick(60)

        
    
        
  

