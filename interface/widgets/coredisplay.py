from interface.widgets.assemblydisplay import AssemblyDisplay as AD
from PyQt5.QtWidgets import QGraphicsView, QGraphicsScene, QFrame, QGridLayout, \
    QLabel, QGraphicsItem
from PyQt5.QtGui import QPainterPath, QDrag, QColor
from PyQt5.QtCore import QPoint, QMimeData, Qt
import matplotlib.colors as color
import matplotlib.cm as cmx
import matplotlib.pyplot as plt


class CoreDisplay(QGraphicsView):

    def __init__(self, parent=None):
        super(CoreDisplay, self).__init__()
        # Sets the block up to hold Qgrpahicitems
        self.myScence = QGraphicsScene()
        self.w = self.size().width()
        self.h = self.size().height()
        
        self.setFixedSize(self.w, self.h)
        self.myScence.setSceneRect(0, 0, self.w, self.h)
        self.fitInView(0, 0, self.w, self.h)
        self.setScene(self.myScence)
        
    def build(self, stencil, bu):
        self.stencil = stencil
        self.bu = [[bu[ss] if ss >= 0 else None for ss in s] for s in stencil]
        self.getColorMap()
        # grabbing the rows and columns of the data
        self.numRows = len(self.stencil)
        self.numCols = len(self.stencil[0])
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
        
        
        # switch the positions
        loc1 = (self.xSel, self.ySel)
        loc2 = (self.xRel, self.yRel)
        self.locations[self.xSel][self.ySel], self.locations[self.xRel][self.yRel] = loc2, loc1
        
        self.update()
        
    def getColorMap(self):
        cmap = plt.get_cmap('viridis')

        cNorm = color.Normalize(vmin=0, vmax=100)
        self.scalarMap = cmx.ScalarMappable(norm=cNorm, cmap=cmap)

    def update(self):
        super(CoreDisplay, self).update()
        self.myScence.clear()
        for i in range(self.numRows):
            for j in range(self.numCols):
                # 
                x,y = self.locations[i][j]
                if self.bu[x][y] is None:
                    c = [0, 0, 0]
                else:
                    c = [int(mm * 255) for mm in self.scalarMap.to_rgba(self.bu[x][y])[:-1]]
                color = QColor(*c)
                item = AD("hello{}{}\n{}".format(x, y, self.bu[x][y]), QPoint(j * self.dx, i * self.dy), self.dx, self.dy, self.stencil[x][y], self.bu[x][y], color)
                self.scene().addItem(item)
            
