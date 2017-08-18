import sys, os, math, random
import pygame
from pygame.locals import *

class pRect:

	rWidth = 20
	rHeight = 100

	def __init__(self, x, y):
		self.x = x
		self.y = y
		self.w = pRect.rWidth
		self.h = pRect.rHeight
		self.rectColor = (255,255,255)
		self.collisionRect = None
		self.isCollision = False

	def update(self, bg, ball):

		pos = pygame.mouse.get_pos()
		#self.x = pos[0] #testing only, can't normally move on x in pong
		self.y = pos[1]
		self.collisionRect = pygame.draw.rect(bg, self.rectColor, pygame.Rect(self.x, self.y, self.w, self.h), 0 )

		#paddle checks for collision with ball

		if self.collisionRect.colliderect(ball.collisionRect):
			if self.isCollision == False: #set only once
				self.isCollision = True
				print 'We have COLLISION!' 
				ball.setBallVelocity()
				print 'Ball angle: ' + str(ball.angle)
		else:
			self.isCollision = False

class pBall:

	radius = 10
	defaultSpeed = 2

	def __init__(self, x, y):
		self.x = x
		self.y = y
		self.r = pBall.radius
		self.rectColor = (255,255,255)
		self.collisionRect = None
		#physics
		self.speed = pBall.defaultSpeed
		self.angle = math.pi

	def update(self, bg):

		self.normalizeAngle() #make sure 0 <= angle <= 2pi

		self.move()
		self.x = int(self.x)
		self.y = int(self.y)
		pos = (self.x, self.y)
		#self.x = pos[0] #testing only, can't normally move on x in pong
		#self.y = pos[1]

		#check if out of bounds
		s = bg.get_size()
		bX = s[0]
		bY = s[1]

		if self.x < 0 or self.x > bX:
			print 'CONGRATULATIONS! You made it to a speed of: ' + str(self.speed)
			self.reset(bg)
		# reverse ball if hit ceiling or floor
		elif self.y < 0 or self.y > bY:
			self.reverse()
			self.speed += 1

		self.collisionRect = pygame.draw.circle(bg, self.rectColor, pos, pBall.radius, 0 )

	def setBallVelocity(self):
		'''
		#reverse ball
		if self.angle > 0:
			self.angle -= math.pi
		else:
			self.angle += math.pi
		'''

		if math.cos(self.angle) < 0:
			self.angle = random.uniform(-1 * math.pi/2 + 0.5, math.pi/2 - 0.5) #cos is neg, so make it pos
		else:
			self.angle = random.uniform(math.pi/2 + 0.5, 3*math.pi/2 - 0.5) #cos is pos, so make it neg

		self.speed += 1

	def move(self):
		#self.x += math.sin(self.angle) * self.speed
		#self.y -= math.cos(self.angle) * self.speed
		self.x += math.cos(self.angle) * self.speed
		self.y -= math.sin(self.angle) * self.speed #in window y increases downward

	def reset(self, bg):

		s = bg.get_size()
		w = s[0]
		h = s[1]

		self.x = w/2
		self.y = h/2
		self.speed = pBall.defaultSpeed

	def reverse(self):
		#reverse ball
		'''
		if math.cos(self.angle) > 0: #moving right
			self.angle = -1 * self.angle
		else:
			self.angle += math.pi
		'''

		self.angle = -1 * self.angle

	def normalizeAngle(self):
		while self.angle > 2*math.pi:
			self.angle -= 2*math.pi
		while self.angle < 0:
			self.angle += 2*math.pi



pygame.init()

clock = pygame.time.Clock()

#window
size = width, height = 640, 640
screen = pygame.display.set_mode(size)

#background
bgColor = (0,0,0)
bg = pygame.Surface(screen.get_size())
bg = bg.convert() # convert for blit performance
bg.fill(bgColor) #black

#paddle/ball
lRect = pRect(10,10)
rRect = pRect(width - pRect.rWidth - 10, 10)
ball = pBall(width/2, height/2)

if pygame.font:
	font = pygame.font.Font(None, 24)
	text = font.render('YOU vs YOU', 1, (255,255,255))
	textpos = text.get_rect(centerx=bg.get_width()/2)
	bg.blit(text,textpos)

while 1:

	clock.tick(60)

	for event in pygame.event.get():
		if event.type == pygame.QUIT: sys.exit()

	bg.fill(bgColor) # erase previous BG
	screen.blit(bg, (0,0)) #show bg on screen

	ball.update(bg)
	lRect.update(bg, ball)
	rRect.update(bg, ball)

	bg.blit(text,textpos) #text is last to render and thus on top

	screen.blit(bg, (0,0))
	pygame.display.flip() #show full render
