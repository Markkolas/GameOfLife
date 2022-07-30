import turtle

###CELL CLASS
class Cell(turtle.RawTurtle):
    """
    Cell class. It is a turtle with some convenient methods
    """
    def __init__(self, screen):
        super().__init__(screen)
        super().shape("square")
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
            return 1
        elif self.lives == True and (n < 2 or n > 3):
            return 0

        return -1

    #Forced to use .color method, hide and show diable onclick methods
    def life_or_death(self, *pos):
        #print("Here; %d,%d" %(pos[0],pos[1]))
        if self.lives == False:
            super().color("green")
            self.lives = True
        elif self.lives == True:
            super().color("blue")
            self.lives = False

###FUNCTIONS USED FOR CELL CREATION AND MANAGEMENT
def init_cells(screen, cols, rows):
    """
    This is what is done:
    CELLS =
    [[],[],[]
    [],dt,[]
    [],[],[]]
    Makes neighbour cheking A LOT eaiser
    """

    #Initialize cells
    cells = []
    #This should be a multiple of 10
    #screensize = screen.screensize()
    #print(screensize)

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
            cell.color("blue")
            cell.onclick(cell.life_or_death)

def life_created(cells, nrow, ncol):
    for row in range(1, nrow+1):
        for col in range(1, ncol+1):
            cell = cells[row][col]
            cell.color("white")
            if cell.lives:
                cell.showturtle()
            else:
                cell.hideturtle()
