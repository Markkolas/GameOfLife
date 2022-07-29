#This is a implementation of game of life using python

import turtle
import time

class Cell(turtle.RawTurtle):
    def __init__(self, screen):
        super().__init__(screen)
        super().shape("square")
        super().color("black")
        super().speed(0)
        super().penup()
        super().shapesize(0.5)
        #super().hideturtle()

        self.lives = False

    def think(self, neighbours):
        """ This is the cell choosing whether is lives or dies, 3 possible outcomes:
         1: It is dead but wants to live
         0: It is alive but wants to be dead
         -1: It wants to remain the same"""
        n = 0
        cont = 0
        for c in neighbours:
            if c is not None:
                n += int(c.lives)
            cont += 1

        if self.lives == False and n == 3:
            super().showturtle()
            return 1
        elif self.lives == True and (n < 2 or n > 3):
            super().hideturtle()
            return 0

        return -1

    #Forced to use .color method, hide and show diable onclick methods
    def life_or_death(self, *pos):
        print("Here; %d,%d" %(pos[0],pos[1]))
        if self.lives == False:
            super().color("white")
            self.lives = True
        elif self.lives == True:
            super().color("black")
            self.lives = False

    def check(self, *pos):
        if self.lives == True:
            print("Im alive!")
        else:
            print("Im dead!")

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

def create_life(cells, nrow, ncol):
    for row in range(1, nrow+1):
        for col in range(1, ncol+1):
            cell = cells[row][col]
            cell.onclick(cell.life_or_death)

def life_created(cells, nrow, ncol):
    for row in range(1, nrow+1):
        for col in range(1, ncol+1):
            cell = cells[row][col]
            #cell.onclick(cell.check)
            cell.color("white")
            if cell.lives:
                cell.showturtle()
            else:
                cell.hideturtle()
def main():
    while True:
        living_ones = []
        dead_ones = []
        for row in range(1, ROW_CELLS+1):
            for col in range(1, COL_CELLS+1):
                cell = cells[row][col]
                neighbours = [cells[row+1][col], cells[row+1][col+1], cells[row+1][col-1],
                              cells[row][col-1],                      cells[row][col+1],
                              cells[row-1][col], cells[row-1][col+1], cells[row-1][col-1]]
                state = cell.think(neighbours)
                if state == 1:
                    living_ones.append([row, col])
                elif state == 0:
                    dead_ones.append([row,col])

        for row, col in living_ones:
            cells[row][col].lives = True
        for row, col in dead_ones:
            cells[row][col].lives = False

        screen.update()
        time.sleep(0.2)

def finish_setup():
    screen.tracer(0,0)
    screen.onkeypress("None", "space")
    life_created(cells, ROW_CELLS, COL_CELLS)
    main()



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

create_life(cells, ROW_CELLS, COL_CELLS)
screen.tracer(1,0)
screen.onkeypress(finish_setup, "space")
screen.listen()
#screen.update()
print("Ready")
#main()
screen.mainloop()
