#This is a implementation of game of life using python

import turtle
import time

class Cell(turtle.RawTurtle):
    def __init__(self, screen):
        super().__init__(screen)
        super().shape("square")
        super().color("white")
        super().speed(0)
        super().penup()
        super().shapesize(0.5)
        super().hideturtle()

        self.lives = False

    def live(neighbours):
        pass

def init_cells(screen, cols, rows):
    #Initialize cells
    cells = []
    #This should be a multiple of 10
    screensize = screen.screensize()
    print(screensize)
    for y in range(rows):
        holder = []
        for x in range(cols):
            cell = Cell(screen)
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
ROW_CELLS = 60
COL_CELLS = 80

cells = init_cells(screen, ROW_CELLS, COL_CELLS)

for row in range(ROW_CELLS):
    for col in range(COL_CELLS):
        cell = cells[row][col]
        neighbours = [cells[row+1][col], cells[row+1][col+1], cells[row+1][col-1],
                      cells[row][col-1],                      cells[row][col+1],
                      cells[row-1][col], cells[row-1][col+1],cells[row-1][col-1]]
screen.update()
input()
