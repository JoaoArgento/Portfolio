import pygame
from random import randint
from settings import *
import math


class Camera(pygame.sprite.Group):
	def __init__(self):
		super().__init__()
		self.offset = pygame.math.Vector2()

		self.display_surface = pygame.display.get_surface()
		self.bg_surface = pygame.image.load('sprites/ArteDoJogo/bgFinal.png').convert_alpha()
		self.bg_rect = self.bg_surface.get_rect(topleft = (0, 0))

		#camera offset 
		self.width = self.display_surface.get_size()[0] //2
		self.height = self.display_surface.get_size()[1] //2

	def center_player(self, player):

		self.offset.x = player.rect.centerx - self.width

		if self.offset.x <= 0:
			self.offset.x = 0
			
		elif self.offset.x > self.bg_surface.get_size()[0]//2:
			self.offset.x = self.bg_surface.get_size()[0]//2
			
		
		self.offset.y = player.rect.centery -  self.height

		if self.offset.y <= 0:
			self.offset.y = 0
			
		elif self.offset.y > self.bg_surface.get_size()[1]//2:
			self.offset.y = self.bg_surface.get_size()[1]//2
			

	def custom_draw(self, player, insta_kill):

	
		self.center_player(player)

	
		bg_offset = self.bg_rect.topleft - self.offset 
		self.display_surface.blit(self.bg_surface, bg_offset)

		for sprite in self.sprites():
			offset_pos = sprite.rect.topleft - self.offset
			sprite_rect = (offset_pos.x, offset_pos.y, sprite.width, sprite.height + 16)
			self.display_surface.blit(sprite.image, sprite_rect)


			for bullet in bullet_group:

				if bullet.rect.colliderect(sprite_rect):
					if sprite.name == "enemy":
						sprite.life -= 1
						bullet.kill()

						if sprite.life <= 0:
							sprite.kill_enemy(player, insta_kill)

					if sprite.name == "Mage":
						bullet.kill()
						print(sprite.life_mage)
						sprite.life_mage -= 1


						if sprite.life_mage <= 0:
							sprite.kill_mage(player, insta_kill)



		





			
		
			


			



		