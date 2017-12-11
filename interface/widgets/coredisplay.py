from interface.widgets.assemblydisplay import AssemblyDisplay as AD
from PyQt5.QtWidgets import QGraphicsView, QGraphicsScene, QFrame, QGridLayout, \
    QLabel, QGraphicsItem
from PyQt5.QtGui import QPainterPath, QDrag
from PyQt5.QtCore import QPoint, QMimeData, Qt


class CoreDisplay(QGraphicsView):

    def __init__(self, parent=None):
        super(CoreDisplay, self).__init__()
#         self.view = QGraphicsScene()
        # Sets the block up to hold Qgrpahicitems
        self.myScence = QGraphicsScene()
        self.w = self.size().width()
        self.h = self.size().height()
        
        self.setFixedSize(self.w, self.h)
        self.myScence.setSceneRect(0, 0, self.w, self.h)
        self.fitInView(0, 0, self.w, self.h)
        self.setScene(self.myScence)
        
    def build(self, stencil):
        # grabbing the rows and columns of the data
        self.numRows = len(stencil)
        self.numCols = len(stencil[0])
        self.dx = self.w / self.numCols
        self.dy = self.h / self.numRows
        
        # Creating the locations map for the AssemblyDispaly Information
        self.locations = [[(i,j) for j in range(self.numCols)] for i in range(self.numRows)]
        
        self.update()
            
    def mousePressEvent(self, event):
        # Creataing a new mouse event with old functionallity, along with new
        super(CoreDisplay, self).mousePressEvent(event)
        # block location
        self.xSel = int(event.pos().x() / self.w * (self.numCols))
        self.ySel = int(event.pos().y() / self.h * (self.numRows))
        
    def mouseReleaseEvent(self, event):
        # Creataing a new mouse event with old functionallity, along with new
        super(CoreDisplay, self).mouseReleaseEvent(event)
        # grabs the postition in the list for groud item
        self.xRel = int(event.pos().x() / self.w * (self.numCols))
        self.yRel = int(event.pos().y() / self.h * (self.numRows))
        
        print(self.xRel, self.yRel, self.xSel, self.ySel)
        
        # switch the positions
        loc1 = (self.xSel, self.ySel)
        loc2 = (self.xRel, self.yRel)
        self.locations[self.xSel][self.ySel], self.locations[self.xRel][self.yRel] = loc2, loc1
        
        self.update()
        
        print("Updated Boxes")
        #self.items[self.xSel][self.ySel].update()
        #self.items[self.xRel][self.yRel].update()
        
    def update(self):
        super(CoreDisplay, self).update()
        self.myScence.clear()
        for i in range(self.numCols):
            for j in range(self.numRows):
                # 
                x,y = self.locations[i][j]
                print(i,j,x,y)
                item = AD("hello{}{}".format(x, y), QPoint(i * self.dx, j * self.dy), self.dx, self.dy)
                self.scene().addItem(item)
            
