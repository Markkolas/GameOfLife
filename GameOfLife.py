#This is a implementation of game of life using python

import turtle

screen = turtle.Screen()
screen.setup(800, 600)
screen.bgcolor("black")

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
screen.setworldcoordinates(0,0,800,400)

c = turtle.Turtle()
c.shape("square")
c.color("white")

c1 = turtle.Turtle()
c1.shape("square")
c1.color("white")
c1.penup()
c1.setx(23)
c1.sety(0)

screen.mainloop()
#Initialize turtles
"""
cells = []
for y in range(600):
    for x in range(800):
        holder = []
"""
