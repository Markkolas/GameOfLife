#This is a implementation of game of life using python

import turtle

#Screen setup
screen = turtle.Screen()
screen.setup(width=800, height=600)
screen.title("Game of life")
screen.bgcolor("black")
screen.tracer(0)

cell = turtle.Turtle()
#cell.shape("square")
cell.color("white")
#cell.shapesize(stretch_wid=5, stretch_len=5)

#Initialize turtles
"""
cells = []
for y in range(600):
    for x in range(800):
        holder = []
"""
