from settings import *

class Explosion(pygame.sprite.Sprite):
	def __init__(self, x, y, width, height, group):
		super().__init__(group)
		self.name = "Explosion"
		self.x = x
		self.y = y
		self.width	= width	
		self.height	= height
		self.animation_list = [explosion1, explosion2, explosion3, explosion4, explosion5, explosion6]
		self.index = 0
		self.image = self.animation_list[self.index]
		self.rect = self.image.get_rect(center = (self.x, self.y))


	def animation(self):
		self.index += 0.1

		if self.index >= len(self.animation_list) - 2:
			self.index = 0
			self.kill()

		self.image = self.animation_list[int(self.index)]


	def update(self):
		self.animation()
		