import pygame
import pygame.mixer
import sys
import math
from pygame.locals import *
from random import randint
from player import Player
from settings import *
from bullet import Bala
from enemy import Enemy
from boss import Boss
from mage import Mage
from itens import Items
from explosion import Explosion
from camera import Camera


pygame.init()


pygame.display.set_caption("grande dia")

#icon = pygame.image.load("").convert_alpha()
# pygame.display.set_icon(icon)
camera_group = Camera()
player = Player(600, 300, 32, 32, 70, 300, [player_group, camera_group])




insta_kill = False
ka_boom = False
draw_kaboom = False
draw_insta_kill = False
max_ammo = False
double_points = False
ka_boom_timer = 60
duration_double = 600
insta_duration = 600
double_xp = False

class Game:
    def __init__(self, insta_kill, ka_boom, double_xp, double_points):
        self.state = "menu"
        
        self.round = 1

        #timer do roundelf.offset.y = player.rect.centery - self.height
        self.round_event = pygame.USEREVENT + 1
        self.round_changed = 1
        pygame.time.set_timer(self.round_event, self.round_changed)
        self.turn_round = True
        self.round_count = 500

        #timer dos enemies
        self.enemy_event = pygame.USEREVENT + 2
        self.enemy_timer = randint(10000, 20000)//100
        pygame.time.set_timer(self.enemy_event, self.enemy_timer)
        self.enemy_count = 20

        #timer dos itens.
        self.item_event = pygame.USEREVENT + 3
        self.item_timer = 10
        pygame.time.set_timer(self.item_event, self.item_timer)
        self.item_count = randint(120, 150)

        #timer do tiro do mago
        self.mage_shooting_event = pygame.USEREVENT + 4
        self.mage_shooting_timer = 3000//100
        pygame.time.set_timer(self.mage_shooting_event, self.mage_shooting_timer)
        self.mage_shooting_count = 100

        #atributos de controle.
        self.points_tracker = 15

        #variaveis de controle dos itens
        self.insta_kill = insta_kill
        self.ka_boom = ka_boom
        self.double_xp = double_xp
        self.double_points = double_points
        self.duration_double = 600
        self.insta_duration = 600
        self.ka_boom_timer = 60

        self.clicking = False 
        self.boss_is_alive  = False
        self.boss_timer = 120
        self.mult = 1
        self.max_ammo_pos_x = randint(10, bg_size[0] - 100) 
        self.max_ammo_pos_y = randint(30, bg_size[1] - 100)
        self.player_is_dead = False
    


    def menu(self):

        screen.blit(imagemMenu, (largura // 4 + 35, 0))
            
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
                           
        button_play.update(screen)
        button_quit.update(screen)

        pygame.display.flip()
        clock.tick(60)

    def game(self, enemy_mult, instakill, kaboom, doublexp, mage, player, enemy):

        pygame.mouse.set_visible(False)

        round_surf = round_font.render(f'Round {self.round}', False, (255, 0, 0))


        ammo_surf = font.render(f'Ammunition: {player.ammo}', False, (255,255,255))
        ammo_rect = ammo_surf.get_rect(topleft=(1050, 60))

        #pontos.
        score_surf = font.render(f'Points: {player.points}', False, (255,255,255))
        score_rect = score_surf.get_rect(topleft=(1050, 20))

        #esse é o if responsavel por mudar de round.
        if player.points >= self.points_tracker and self.round <= 3:
            self.points_tracker += 15
            self.turn_round = True
            enemy_mult += 1
            self.round += 1
            round_surf = round_font.render(f'Round {self.round}', False, (255, 0, 0))

            #se o round for maior que 3, ele para de mudar de round.
            if self.round >= 3:
                self.turn_round = False      

       
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
                    
                #timers.
            elif event.type == self.mage_shooting_event and len(mage_group) > 0:
                self.mage_shooting_count -= 1   

            elif event.type == self.enemy_event:
                self.enemy_count -= 1

            elif event.type == self.round_event and self.turn_round:
                self.round_count -= 1

            elif event.type == self.item_event:
                self.item_count -= 1

            elif event.type == MOUSEBUTTONDOWN:
                self.clicking = True
            
            elif event.type == MOUSEBUTTONUP:
                self.clicking = False 

            if self.clicking:
                player.atirar(mouseX, mouseY)

                                         
        # logica dos timers
        if self.round >= 1 and self.round < 4:
            if self.round_count <= 0:
                self.turn_round = False
                self.round_count = 500
                #criando um item aleatorio.
            if not self.turn_round:
                if self.item_count <= 0:

                    choice_item = randint(1, 3)
                    if choice_item == 1:
                        doublexp = Items(randint(10, bg_size[0] - 100),randint(30, bg_size[1]- 100), 32, 32, [double_point_group, camera_group])
                        self.double_xp = True
                        duration_double = 600
                        double_point_group.add(doublexp)
                        camera_group.add(doublexp)

                            

                    elif choice_item == 2:
                        instakill = Items(randint(10,  bg_size[0] - 100),randint(30,  bg_size[1] - 100), 32, 32, [insta_kill_group, camera_group])
                        insta_kill_group.add(instakill)
                        camera_group.add(instakill)
                        
                        
                            

                    elif choice_item == 3:
                        kaboom = Items(randint(10,  bg_size[0] - 100),randint(30,  bg_size[1] - 100), 32, 32, [ka_boom_group, camera_group]) 
                        ka_boom_group.add(kaboom)
                        camera_group.add(kaboom)
                            
                    self.item_count = randint(120, 200)
                       
                if not player.isDead:
                         #tiro do mago.
                    if self.mage_shooting_count <= 0:
                        mage.atirar(self.mage_shooting_count, mage_bullet_angle, camera_group)
                        self.mage_shooting_count = 100

                    if self.round == 1:
                        if self.enemy_count <= 0 and len(enemy_group) <= 4:
                            criar_enemy()
                            self.enemy_count = 20
                
                    if self.round >= 2:

                        if self.enemy_count <= 0:

                            choice_enemy = randint(1,2)

                            if choice_enemy == 1  and len(mage_group) <= 4:                   
                                criar_mage(mage)

                            elif choice_enemy == 2 and len(enemy_group) <= 10:
                                criar_enemy()

                            self.enemy_count = 20

          

                
            if player.life > 0: 
              #desenhando o player
                camera_group.update()
                camera_group.custom_draw(player, insta_kill)
                player.criarvida()
                player.animate_player()  
                screen.blit(ammo_surf, ammo_rect)
                screen.blit(score_surf, score_rect)




                if player.ammo <= 0:
                    self.max_ammo_pos_x = randint(10, bg_size[0] - 100) 
                    self.max_ammo_pos_y = randint(30, bg_size[1] - 100)
                    max_ammo_group.add(maxammo)
                    camera_group.add(maxammo)


                for item in max_ammo_group:
                    item.desenhomaxammo(screen)

                max_collision = pygame.sprite.spritecollide(player, max_ammo_group, True, pygame.sprite.collide_mask)

                if max_collision:
                    player.ammo = player.start_ammo
                    maxammo.PlayMusicMaxAmmo()        

                    # mantendo o double na tela caso double_xp for igual a rue
                for item in double_point_group:
                    item.desenhodoublexp(screen)
                        # quando a duração do double for 0, vai tirar o double.

                for item in insta_kill_group:
                    item.desenhoinstakill(screen)

                
                for item in ka_boom_group:
                    item.desenhokaboom(screen)

                    #colisão dos itens.
                insta_collision = pygame.sprite.spritecollide(player, insta_kill_group, True, pygame.sprite.collide_mask)
                double_collision = pygame.sprite.spritecollide(player, double_point_group, True, pygame.sprite.collide_mask)
                kaboom_collision = pygame.sprite.spritecollide(player, ka_boom_group, True, pygame.sprite.collide_mask)

                    # colisão do item double point
                if double_collision:
                    doublexp.PlayMusicDoublexp()
                    self.double_points = True
                    self.double_xp = False

                    # colisao do item kaboom
                elif kaboom_collision:
                    self.ka_boom = True
                    kaboom.PlayMusicKaboom()
                    self.kaboom = False
                        
                        
                    # Insta Kill
                elif insta_collision:
                    self.insta_kill = True
                    instakill.PlayMusicInstaKill()
                    self.insta_duration = 600


                if self.double_points:
                    self.mult = 2
                    self.duration_double -= 1
                    

                else:
                    self.mult = 1

                if self.duration_double <= 0:
                    self.double_points = False
                    self.duration_double = 600

                if self.insta_kill:
                    self.insta_duration -= 1

                    if self.insta_duration <= 0:
                        self.insta_kill = False
                        self.insta_duration = 600

                if self.ka_boom:
                    if self.ka_boom_timer > 0:
                        self.ka_boom_timer -= 1
                        for enemy in enemy_group:
                            explosion = Explosion(enemy.rect.centerx, enemy.rect.centery, 32, 32, camera_group)
                            explosion_group.add(explosion)
                            enemy.kill()
                            player.points += 1

                        for mage in mage_group:
                            explosion = Explosion(mage.rect.centerx, mage.rect.centery, 32, 32, camera_group)
                            explosion_group.add(explosion)
                            mage.kill()
                            player.points += 1
                            


                    else:
                        self.ka_boom = False
                        self.ka_boom_timer = 60
            else:
                screen.blit(player_death_surf, player_death_rect)
                self.player_is_dead = True
    

               
            #caso os rounds se passarem, o boss será criado.
        else:
            boss_surf = boss_font.render(f'O brabo foi criado...', False, (0,0,0))
            boss_rect = boss_surf.get_rect(center = (largura//2, altura//2))
            if self.boss_timer > 0:
                #screen.blit(boss_surf,boss_rect)
                self.boss_timer -= 1 
            else:
                self.boss_timer = 0 
                self.boss_is_alive = True
            
            if self.boss_is_alive:
                boss_group.add(boss)
                    
            if not self.boss_is_alive:   
                    screen.blit(player_win_surf, player_win_rect)
                
               
        
        if self.turn_round:
            screen.blit(round_surf, round_rect)

        keys = pygame.key.get_pressed()

        if keys[pygame.K_SPACE] and self.player_is_dead:
            player.life = 300
            player.target_life = 300
            player.ammo = 70
            player.points = 0
            enemy.life = 3 
            mage.life_mage = 5 
            self.round = 1
            self.turn_round = True
            enemy_group.empty()
            mage_group.empty()
            self.player_is_dead = False




       

        
            

        ponteiro_group.draw(screen)
        ponteiro_group.update() 

        bullet_group.draw(screen)
        bullet_group.update()

        pygame.display.flip()
        clock.tick(60)

    #mudando o status do game 
    def change_state(self):
        if self.state == "menu":
            self.menu()
        if self.state == "game":
            self.game(enemy_mult, instakill, kaboom, doublexp, mage, player, enemy)

class Button(pygame.sprite.Sprite):
    def __init__(self, x, y, image):
        super().__init__()
        self.x = x
        self.y = y
        self.image = image 
        self.rect = self.image.get_rect(center = (self.x, self.y))
        
    def detectar_click(self):
        if pygame.mouse.get_pressed()[0]:
            if self.rect.collidepoint(mouseX, mouseY):
                game_state.state = "game"

            elif self.rect.collidepoint(mouseX,mouseY):
                pygame.quit()
                sys.exit()

    def desenhar_button(self, screen):
        screen.blit(self.image,self.rect)

    def update(self, screen):
        self.desenhar_button(screen)
        self.detectar_click()

#mudando o ponteiro do mouse 
class Ponteiro(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = pygame.image.load("sprites/ponteiro.png").convert_alpha()
        self.rect = self.image.get_rect()

    def update(self):
        self.rect.center = pygame.mouse.get_pos()

#função pra criar os magos e os inimigos
def criar_mage(mage):
    mage = Mage(randint(30, bg_size[0] - 20), randint(30, bg_size[1] - 20),64,64, [mage_group, camera_group], game_state.mult)
    mage_group.add(mage) 

def criar_enemy():
    for x in range(0, 3):
        enemy = Enemy(randint(30, bg_size[0] - 20), randint(30, bg_size[1] - 20),64,64, [enemy_group, camera_group],  game_state.mult)
    


#instanicando os objetos.

button_play = Button(largura/2, altura/2, botaoJogar)
button_quit = Button(largura/2, altura/2 + 200, botaoSair)

#ponteiro
ponteiro = Ponteiro()
ponteiro_group = pygame.sprite.Group()
ponteiro_group.add(ponteiro)

#desenhando o game 
game_state = Game(insta_kill, ka_boom, double_xp, double_points)
maxammo = Items(game_state.max_ammo_pos_x, game_state.max_ammo_pos_y, 32, 32, [max_ammo_group, camera_group])
enemy = Enemy(randint(30, largura - 20), randint(30,altura - 20),64,64, [enemy_group, camera_group], game_state.mult)
doublexp = Items(randint(10, largura - 100), randint(30, altura - 100), 32, 32, [double_point_group, camera_group])
instakill = Items(randint(10, largura - 100),randint(30, altura - 100), 32, 32, [insta_kill_group, camera_group])
kaboom = Items(randint(10, largura - 100), randint(30, altura - 100), 32, 32, [ka_boom_group, camera_group])
boss = Boss(randint(10, largura - 200), randint(30, altura - 100), 64, 64, [boss_group, camera_group])
mage = Mage(randint(30, largura - 20), randint(30,altura - 20),64,64,[mage_group, camera_group], game_state.mult)



round_surf = round_font.render(f'Round {game_state.round}', False, (255, 0, 0))
round_rect = round_surf.get_rect(center = (largura//2, altura//2))


choice_enemy = randint(1,2)
# loop do game
while running:
    mouseX, mouseY = pygame.mouse.get_pos()
    game_state.change_state()
    
    

    

   
