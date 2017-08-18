import sys, math, random
import pygame
from pygame.locals import *
import pymunk
import pymunk.pygame_util
import pymunk.constraint

class Snake:
	def __init__(self):
		self.headBody = None
		self.midBody = None
		self.speed = 1000.0
		self.sections = []

	def addSection(self, space):
		mass = 1
		radius = 15
		moment = pymunk.moment_for_circle(mass, 0, radius) #each body must have inertia
		#bodies are for simulation
		body = pymunk.Body(mass, moment)

		# set body position
		if not self.sections: #if sections empty
			body.position = self.midBody.position[0] + radius*2 + 20, self.midBody.position[1]
		else:
			body.position = self.sections[len(sections)-1].position[0] + 2, self.sections[len(sections)-1].position[1] + 2

		body.friction = 1.0
		#shapes are for collision
		shape = pymunk.Circle(body, radius)
		shape.collision_type = 1

		# set body constraint
		if not self.sections:
			c = pymunk.constraint.SlideJoint(self.midBody, body, (0,0), (0,0), 0, radius*2 + 6)
			print 'Connecting to mid'
			print str(len(sections))
		else:
			c = pymunk.constraint.SlideJoint(self.sections[len(sections)-1], body, (0,0), (0,0), 0, radius*2 + 6)
			print 'Connecting to section ' + str(self.sections[len(sections)-1])

		space.add(body, shape, c)
		self.sections.append(body)

	def makeSnake(self, bg, space):
		#head
		headMass = 2
		headMoment = pymunk.moment_for_circle(headMass, 0, 17)	
		headBody = pymunk.Body(headMass, headMoment)

		scSize = bg.get_size()
		scWidth = scSize[0]
		scHeight = scSize[1]

		headBody.position = (scWidth/2, scHeight/2) 
		headBody.friction = 1.0
		headShape = pymunk.Circle(headBody,17)
		headShape.collision_type = 3

		self.headBody = headBody
		space.add(headBody,headShape)
		#mid
		midMass = 1
		radius = 15
		midMoment = pymunk.moment_for_circle(midMass, 0, radius)	
		midBody = pymunk.Body(midMass, midMoment)

		midBody.position = (headBody.position[0] + radius*2 + 20, headBody.position[1]) 
		midBody.friction = 1.0
		midShape = pymunk.Circle(midBody,radius)
		midShape.collision_type = 0


		c1 = pymunk.constraint.SlideJoint(headBody, midBody, (0,0), (0,0), 0, radius*2 + 6)

		self.midBody = midBody
		space.add(midBody,midShape, c1)

		#return headBody, midBody

	def up(self):
		force = (0.0, self.speed)
		self.headBody.apply_force_at_local_point(force, (0.0,0.0))

	def down(self):
		force = (0.0, -1 * self.speed)
		self.headBody.apply_force_at_local_point(force, (0.0,0.0))

	def left(self):
		force = (-1 * self.speed, 0.0)
		self.headBody.apply_force_at_local_point(force, (0.0,0.0))

	def right(self):
		force = (self.speed, 0.0)
		self.headBody.apply_force_at_local_point(force, (0.0,0.0))

### END SNAKE ###

def addStatic(bg, space):
	body = pymunk.Body(body_type = pymunk.Body.STATIC) #static is different from dynamic
	x = random.randint(10, bg.get_size()[0]-10)
	y = random.randint(10, bg.get_size()[1]-10)
	body.position = (x, y)

	poly = pymunk.Poly.create_box(body, radius=1)
	poly.collision_type = 2

	space.add(poly)
	return poly

pygame.init()
clock = pygame.time.Clock()

#window
size = width, height = 640, 640
screen = pygame.display.set_mode(size)

#DEBUG drawing tools that pymunk has built in for pygame
drawOptions = pymunk.pygame_util.DrawOptions(screen)

#physics
space = pymunk.Space()
space.gravity = (0.0,0.0)
space.damping = 0.2

#background
bgColor = (0,0,0)
bg = pygame.Surface(screen.get_size())
bg = bg.convert() # convert for blit performance
bg.fill(bgColor) #black

if pygame.font:
	font = pygame.font.Font(None, 24)
	text = font.render('SNAKE', 1, (255,255,255))
	textpos = text.get_rect(centerx=bg.get_width()/2, centery=10)
	bg.blit(text,textpos)

#game
snake = Snake()
sections = []
pelletsEaten = 0

snake.makeSnake(bg, space)
snake.addSection(space)
addStatic(bg, space)

print snake.sections

isUp = False
isDown = False
isLeft = False
isRight = False

#main loop
while 1:

	clock.tick(60)

	for event in pygame.event.get():
		if event.type == pygame.QUIT: 
			sys.exit()
		elif event.type == KEYDOWN:
			if event.key == K_w:
				isUp = True
			if event.key == K_s:
				isDown = True
			if event.key == K_a:
				isLeft = True
			if event.key == K_d:
				isRight = True
		elif event.type == KEYUP:
			if event.key == K_w:
				isUp = False
			if event.key == K_s:
				isDown = False
			if event.key == K_a:
				isLeft = False
			if event.key == K_d:
				isRight = False

	if isUp:
		snake.up()
	if isDown:
		snake.down()
	if isLeft:
		snake.left()
	if isRight:
		snake.right()

	bg.fill(bgColor) # erase previous BG
	screen.blit(bg, (0,0)) #show bg on screen

	#collision
	def collision(arb):
		global pelletsEaten

		if arb.is_first_contact:
			for shape in arb.shapes:
				if shape.collision_type == 0:
					print 'Collision with Mid'
				if shape.collision_type == 1:
					print 'Collision with section'
				if shape.collision_type == 2:
					print 'Collision with static'
					space.remove(shape)
					addStatic(bg, space)
					snake.addSection(space)
					snake.speed += 200
					pelletsEaten += 1

	snake.headBody.each_arbiter(collision)
	#update
	space.step(1/50.0)

	
	#DEBUG DRAW
	space.debug_draw(drawOptions)
	white = (255,255,255)
	screen.blit(font.render("SNAKE", 1, white), (0,0))
	screen.blit(font.render("fps: " + str(clock.get_fps()), 1, white), (0,20))
	screen.blit(font.render("Pellets eaten: " + str(pelletsEaten), 1, white), (0,40))

	pygame.display.flip() #show full render