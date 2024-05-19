#This is a implementation of game of life using python
from life_utils import *
import time

def main():
    while True:
        living_ones = []
        dead_ones = []
        for row in range(1, ROW_CELLS+1):
            for col in range(1, COL_CELLS+1):
                cell = CELLS[row][col]
                neighbours = [CELLS[row+1][col], CELLS[row+1][col+1], CELLS[row+1][col-1],
                              CELLS[row][col-1],                      CELLS[row][col+1],
                              CELLS[row-1][col], CELLS[row-1][col+1], CELLS[row-1][col-1]]
                state = cell.think(neighbours)
                if state == 1:
                    living_ones.append([row, col])
                elif state == 0:
                    dead_ones.append([row,col])

        for row, col in living_ones:
            CELLS[row][col].lives = True
            CELLS[row][col].showturtle()
        for row, col in dead_ones:
            CELLS[row][col].lives = False
            CELLS[row][col].hideturtle()

        #This is better compared to using the event loop.
        #This pair of lines can became your worst nightmare in other apps.
        #You have been advised of the danger.
        """
        Flow diagram:

        START---USER EVENTS---USER PRESS SPACEBAR
                                     |-------MAIN <----- Now the event loop is locked
        """
        SCREEN.update()
        time.sleep(0.1)

def finish_setup():
    SCREEN.tracer(0,0)
    SCREEN.bgcolor("black")
    SCREEN.onkeypress("None", "space")
    life_created(CELLS, ROW_CELLS, COL_CELLS)
    main()



SCREEN = turtle.Screen()
SCREEN.setup(980, 740)
SCREEN.bgcolor("black")
SCREEN.tracer(0,0)

"""
Cell size: 11x11p
Separation between CELLS: 1p

CELLS in row/column: 80/60
Row size: 11*80+79=959
Col size: 11*60+59=719

SCREEN size: 960x720
"True" world size: 949x709

The "SCREEN" contains the "world"

(0,720)--------------(960,720)
  |                      |
  |                      |
  |        WORLD         |
  |                      |
  |                      |
(0,0)----------------(960,0)
"""
SCREEN.setworldcoordinates(0,0,960,720)
ROW_CELLS = 60
COL_CELLS = 80

CELLS = init_cells(SCREEN, COL_CELLS+2, ROW_CELLS+2)

create_life(CELLS, ROW_CELLS, COL_CELLS)

SCREEN.tracer(1,0)
SCREEN.onkeypress(finish_setup, "space")
SCREEN.listen()

SCREEN.mainloop()
