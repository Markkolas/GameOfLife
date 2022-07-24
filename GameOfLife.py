#This is a implementation of game of life using python

import turtle

screen = turtle.Screen()
screen.setup(820, 620)
screen.bgcolor("black")
screen.tracer(0,0)

"""
Screen size: 800x600

(0,600)--------------(800,600)
  |                      |
  |                      |
  |       SCREEN         |
  |                      |
  |                      |
(0,0)----------------(800,0)
"""
screen.setworldcoordinates(0,0,800,600)

#Initialize painter
the_painter = turtle.Turtle()
the_painter.shape("square")
the_painter.color("white")
the_painter.speed(0)
the_painter.shapesize(0.5)
the_painter.penup()

#This should be a multiple of 10
screensize = screen.screensize()
print(screensize)
for y in range(int(screensize[1]/10)):
    for x in range(int(screensize[0]/10)):
        the_painter.goto(10*x+10,10*y+10)
        the_painter.stamp()
        screen.update()

input()
