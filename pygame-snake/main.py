import pygame, os, time, random

from pygame import event
from pygame.display import Info


BOX_PX = 16
SCREEN_WIDTH, SCREEN_HEIGHT = 40, 40
WIN = pygame.display.set_mode((SCREEN_WIDTH*BOX_PX, SCREEN_HEIGHT*BOX_PX))

IMG_PATH = "OneDrive\\Documents\\PythonProjects\\SnakeGame\\images"
WHITE_BOX = pygame.image.load(os.path.join(IMG_PATH, "white.png")).convert()
RED_BOX = pygame.image.load(os.path.join(IMG_PATH, "red.png")).convert()
GREEN_BOX = pygame.image.load(os.path.join(IMG_PATH, "green.png")).convert()

UP = (0, -1)
DOWN = (0, 1)
LEFT = (-1, 0)
RIGHT = (1, 0)

class SNAKE:
    def __init__(self) -> None:
        self.length = 2
        self.position = [((SCREEN_WIDTH*BOX_PX)/2, (SCREEN_HEIGHT*BOX_PX)/2)]
        self.direction = RIGHT
    
    def get_head_position(self):
        return self.position[0]

    def draw(self):
        for i in range(0,len(self.position)):
            WIN.blit(RED_BOX,(self.position[i][0],self.position[i][1]))

    def move(self):
        x,y = self.direction
        new = (self.position[0][0]+(BOX_PX*x)) % (SCREEN_WIDTH*BOX_PX), (self.position[0][1]+(BOX_PX*y) % (SCREEN_HEIGHT*BOX_PX) 
        


        if len(self.position) > 2 and new in self.position[2:]:
            self.reset()
            self.position = [(new)]

        else:    
            self.position.insert(0, new)
            if self.length < len(self.position):
                    self.position.pop()
        
    def reset(self):
        self.length = 2

    def turn(self, point):
        x, y = self.direction
        if (-x,-y) == point:
            return
        else:
            self.direction = point

    def handle_keys(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_UP:
                    self.turn(UP)
                elif event.key == pygame.K_DOWN:
                    self.turn(DOWN)
                elif event.key == pygame.K_LEFT:
                    self.turn(LEFT)
                elif event.key == pygame.K_RIGHT:
                    self.turn(RIGHT)

        

class FOOD:
    def __init__(self) -> None:
        self.position = ((random.randint(0,39)*BOX_PX),(random.randint(0,39)*BOX_PX))

    def get_position(self):
        return self.position

    def randomize(self):
        self.position = ((random.randint(0,39)*BOX_PX),(random.randint(0,39)*BOX_PX))

    def draw(self):
        WIN.blit(GREEN_BOX, (self.position[0],self.position[1]))

def draw_bg():
    for i in range(0, SCREEN_WIDTH):
        for j in range(0, SCREEN_WIDTH):
            WIN.blit(WHITE_BOX, (i*BOX_PX, j*BOX_PX))

def main():

    snake = SNAKE()
    food = FOOD()

    clock = pygame.time.Clock()

    while True:
        if snake.get_head_position() == food.get_position():
            while True:
                if food.position in snake.position:
                    food.randomize()
                else: 
                    break
            snake.length += 1


        clock.tick(15)
        draw_bg()
        snake.handle_keys()
        snake.move()
        food.draw()
        snake.draw()
        pygame.display.update()
        print(snake.get_head_position())



if __name__ == "__main__":
    main()
