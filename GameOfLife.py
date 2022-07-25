#This is a implementation of game of life using python

import turtle
import time

def init_cells(screen):
    #Initialize cells
    cells = []
    #This should be a multiple of 10
    screensize = screen.screensize()
    print(screensize)
    for y in range(60): #Rows
        holder = []
        for x in range(80): #Cols
            cell = turtle.RawTurtle(screen)
            cell.shape("square")
            cell.color("white")
            cell.speed(0)
            cell.penup()
            cell.shapesize(0.5)
            cell.hideturtle()
            cell.lives = False
            #The x*2 is for a separation of 1px between cells.
            #This works due to the nature of the loop
            cell.goto(10*x+2*x,10*y+2*y)
            holder.append(cell)
        cells.append(holder)
    return cells


screen = turtle.Screen()
screen.setup(980, 740)
screen.bgcolor("black")
screen.tracer(0,0)

"""
Cell size: 11x11p
Separation between cells: 1p

Cells in row/column: 80/60
Row size: 11*80+79=959
Col size: 11*60+59=719

Screen size: 960x720
"True" world size: 949x709

The "screen" contains the "world"

(0,720)--------------(960,720)
  |                      |
  |                      |
  |        WORLD         |
  |                      |
  |                      |
(0,0)----------------(960,0)
"""
screen.setworldcoordinates(0,0,960,720)

cells = init_cells(screen)
screen.update()
input()
