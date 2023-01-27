import pygame
from settings import *

class Items(pygame.sprite.Sprite):
	def __init__(self, x, y, width, height, group):
		super().__init__()
		self.name = "idk"
		self.x = x
		self.y = y
		self.width = width
		self.height = height
		self.image = pygame.Surface((self.width, self.height))
		self.rect = self.image.get_rect(center=(self.x, self.y))
		self.mask = pygame.mask.from_surface(self.image)
		

	def desenhomaxammo(self, screen):
		self.image = maxammo
		self.mask = pygame.mask.from_surface(self.image)
		
		
	def PlayMusicMaxAmmo(self):
		max_ammo_sound.play(loops = 0)
		max_ammo_sound.set_volume(0.05)

	def desenhodoublexp(self, screen):
		self.image = doublepoints
		self.mask = pygame.mask.from_surface(self.image)
		

	def PlayMusicDoublexp(self):
		double_points_sound.play(loops=0)
		double_points_sound.set_volume(0.05)

	def desenhoinstakill(self, screen):
		self.image = instakill
		self.mask = pygame.mask.from_surface(self.image)
		

	def PlayMusicInstaKill(self):
		insta_kill_sound.play(loops=0)
		insta_kill_sound.set_volume(0.05)

	def desenhokaboom(self, screen):
		self.image = nuke
		self.mask = pygame.mask.from_surface(self.image)
		

	def PlayMusicKaboom(self):
		ka_boom_sound.play(loops=0)
		ka_boom_sound.set_volume(0.05)