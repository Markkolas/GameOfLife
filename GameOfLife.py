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

    def live(self, neighbours):
        n = 0
        for c in neighbours:
            if c is not None:
                n += int(c.lives)

        if self.lives == False and n == 3:
            super().showturtle()
            self.lives = True
        elif self.lives == True and (n < 2 or n > 3):
            super().hideturtle()
            self.lives = False


def init_cells(screen, cols, rows):
    #Initialize cells
    cells = []
    #This should be a multiple of 10
    screensize = screen.screensize()
    print(screensize)

    for y in range(rows):
        holder = []
        for x in range(cols):
            if y == 0 or y == rows-1:
                holder.append(None)
            else:
                if x == 0 or x == cols-1:
                    holder.append(None)
                else:
                    cell = Cell(screen)
                    #The x*2 is for a separation of 1px between cells.
                    #The (x-1) part is because how the array is constructed.
                    #This works due to the nature of the loop
                    cell.goto(10*(x-1)+2*x,10*(y-1)+2*y)
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

"""
This is what is done:
cells =
 [[],[],[]
  [],dt,[]
  [],[],[]]
Makes neighbour cheking A LOT eaiser
"""
cells = init_cells(screen, COL_CELLS+2, ROW_CELLS+2)

cells[54][5].showturtle()
cells[53][6].showturtle()
cells[53][7].showturtle()
cells[52][5].showturtle()
cells[52][6].showturtle()

cells[54][5].lives = True
cells[53][6].lives = True
cells[53][7].lives = True
cells[52][5].lives = True
cells[52][6].lives = True

screen.update()
input()

while True:
    for row in range(1, ROW_CELLS+1):
        for col in range(1, COL_CELLS+1):
            cell = cells[row][col]
            neighbours = [cells[row+1][col], cells[row+1][col+1], cells[row+1][col-1],
                          cells[row][col-1],                      cells[row][col+1],
                          cells[row-1][col], cells[row-1][col+1], cells[row-1][col-1]]
            cell.live(neighbours)
    screen.update()
    print("done!")
    input()
