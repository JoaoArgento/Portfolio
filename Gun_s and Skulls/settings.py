import pygame

#tela, fps

pygame.init()

largura = 1280
altura = 720



screen = pygame.display.set_mode((largura, altura))
clock = pygame.time.Clock()



# sistema de pontos
font = pygame.font.Font('font/Pixeltype.ttf', 50)
round_font = pygame.font.Font('font/Pixeltype.ttf', 128)
boss_font = pygame.font.Font('font/Pixeltype.ttf', 128)
player_font = pygame.font.Font('font/Pixeltype.ttf', 128)

# sons
max_ammo_sound = pygame.mixer.Sound("sons/maxammo.wav")
double_points_sound = pygame.mixer.Sound("sons/doublepoints.wav")
insta_kill_sound = pygame.mixer.Sound("sons/instakill.wav")
ka_boom_sound = pygame.mixer.Sound("sons/kabom.wav")
explosion_sound = pygame.mixer.Sound("sons/explosion2.wav")


player_death_surf = player_font.render(f'''You Died!''', False, (0, 0, 0))

player_death_rect = player_death_surf.get_rect(center = (largura//2, altura//2))

player_win_surf = player_font.render(f'You win', False, (0,0,0))
player_win_rect = player_win_surf.get_rect(center = (largura//2, altura//2))


ammo = 30
start_ammo = 70

#bg
bg = pygame.image.load('sprites/ArteDoJogo/bgFinal.png').convert_alpha()
bg_size = bg.get_size()

#player
player_idle_1 = pygame.image.load("sprites/idle/idle0.png").convert_alpha()
player_idle_2 = pygame.image.load("sprites/idle/idle1.png").convert_alpha()
player_idle_3 = pygame.image.load("sprites/idle/idle2.png").convert_alpha()
player_idle_4 = pygame.image.load("sprites/idle/idle3.png").convert_alpha()
player_idle_5 = pygame.image.load("sprites/idle/idle4.png").convert_alpha()

# imagens da animação de walk do player
player_walk_1 = pygame.image.load("sprites/walk/walk0.png").convert_alpha()
player_walk_2 = pygame.image.load("sprites/walk/walk1.png").convert_alpha()
player_walk_3 = pygame.image.load("sprites/walk/walk2.png").convert_alpha()
player_walk_4 = pygame.image.load("sprites/walk/walk3.png").convert_alpha()
player_walk_5 = pygame.image.load("sprites/walk/walk4.png").convert_alpha()
player_walk_6 = pygame.image.load("sprites/walk/walk5.png").convert_alpha()


#imagens da animação do enemy.
explosion1 = pygame.transform.scale(pygame.image.load("sprites/ArteDoJogo/caveiraExplosao0.png").convert_alpha(), (64,64))
explosion2 = pygame.transform.scale(pygame.image.load("sprites/ArteDoJogo/caveiraExplosao1.png").convert_alpha(), (64,64))
explosion3 = pygame.transform.scale(pygame.image.load("sprites/ArteDoJogo/caveiraExplosao2.png").convert_alpha(), (64,64))
explosion4 = pygame.transform.scale(pygame.image.load("sprites/ArteDoJogo/caveiraExplosao3.png").convert_alpha(), (64,64))
explosion5 = pygame.transform.scale(pygame.image.load("sprites/ArteDoJogo/caveiraExplosao4.png").convert_alpha(), (64,64))
explosion6 = pygame.transform.scale(pygame.image.load("sprites/ArteDoJogo/caveiraExplosao5.png").convert_alpha(), (64,64))

#mage
mage_idle_1 = pygame.image.load("sprites/ArteDoJogo/esqueletoMago0.png").convert_alpha()
mage_idle_2 = pygame.image.load("sprites/ArteDoJogo/esqueletoMago1.png").convert_alpha()
mage_idle_3 = pygame.image.load("sprites/ArteDoJogo/esqueletoMago2.png").convert_alpha()
mage_idle_4 = pygame.image.load("sprites/ArteDoJogo/esqueletoMago3.png").convert_alpha()
mage_idle_5 = pygame.image.load("sprites/ArteDoJogo/esqueletoMago4.png").convert_alpha()

mage_atk_1 = pygame.image.load("sprites/ArteDoJogo/esqueletoMagoAtaque0.png").convert_alpha()
mage_atk_2 = pygame.image.load("sprites/ArteDoJogo/esqueletoMagoAtaque1.png").convert_alpha()
mage_atk_3 = pygame.image.load("sprites/ArteDoJogo/esqueletoMagoAtaque2.png").convert_alpha()
mage_atk_4 = pygame.image.load("sprites/ArteDoJogo/esqueletoMagoAtaque3.png").convert_alpha()

projetilMago_0 = pygame.transform.scale(pygame.image.load("sprites/ArteDoJogo/projetilMago0.png").convert_alpha(), (32,32))
projetilMago_1 = pygame.transform.scale(pygame.image.load("sprites/ArteDoJogo/projetilMago1.png").convert_alpha(), (32,32))
projetilMago_2 = pygame.transform.scale(pygame.image.load("sprites/ArteDoJogo/projetilMago2.png").convert_alpha(), (32,32))
projetilMago_3 = pygame.transform.scale(pygame.image.load("sprites/ArteDoJogo/projetilMago3.png").convert_alpha(), (32,32))
projetilMago_4 = pygame.transform.scale(pygame.image.load("sprites/ArteDoJogo/projetilMago4.png").convert_alpha(), (32,32))

#boss
boss_walk_1 = pygame.image.load("sprites/ArteDoJogo/Bossv2_0.png").convert_alpha()
boss_walk_2 = pygame.image.load("sprites/ArteDoJogo/Bossv2_1.png").convert_alpha()
boss_walk_3 = pygame.image.load("sprites/ArteDoJogo/Bossv2_2.png").convert_alpha()

boss_atk_1 = pygame.image.load("sprites/ArteDoJogo/Bossv2Ataque_0.png").convert_alpha()
boss_atk_2 = pygame.image.load("sprites/ArteDoJogo/Bossv2Ataque_1.png").convert_alpha()
boss_atk_3 = pygame.image.load("sprites/ArteDoJogo/Bossv2Ataque_2.png").convert_alpha()
boss_atk_4 = pygame.image.load("sprites/ArteDoJogo/Bossv2Ataque_3.png").convert_alpha()
boss_atk_5 = pygame.image.load("sprites/ArteDoJogo/Bossv2Ataque_4.png").convert_alpha()

# Imagens dos buffs
instakill = pygame.transform.scale(pygame.image.load("sprites/ArteDoJogo/instakill.png").convert_alpha(),(64,64))
doublepoints = pygame.transform.scale(pygame.image.load("sprites/ArteDoJogo/doublePoints.png").convert_alpha(),(64,64))
nuke = pygame.transform.scale(pygame.image.load("sprites/ArteDoJogo/nuke.png").convert_alpha(),(64,64))
maxammo = pygame.transform.scale(pygame.image.load("sprites/ArteDoJogo/maxAmmo.png").convert_alpha(),(128,64))

# Menu
imagemMenu = pygame.image.load("sprites/ArteDoJogo/Menu.png").convert_alpha()
botaoJogar = pygame.image.load("sprites/ArteDoJogo/botaoJogar.png").convert_alpha()
botaoSair = pygame.image.load("sprites/ArteDoJogo/botaoSair.png").convert_alpha()

#group do player
player_group = pygame.sprite.GroupSingle()

#variaveis de controle 
mult = 1
enemy_mult = 1
points_tracker = 15
mage_bullet_angle = 45
anim_count = False

#variaveis auxiliares.
running = True
clicking = False
boss_is_alive = False
boss_timer = 150
mage_shooting = False

#variaveis de controle dos itens
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

#groups 

bullet_group = pygame.sprite.Group()
enemy_group = pygame.sprite.Group()
mage_group = pygame.sprite.Group()
mage_bullet_group = pygame.sprite.Group()
explosion_group = pygame.sprite.Group()
boss_group = pygame.sprite.Group()

# grupo dos itens
max_ammo_group = pygame.sprite.Group()
double_point_group = pygame.sprite.Group()
insta_kill_group = pygame.sprite.Group()
ka_boom_group = pygame.sprite.Group()

