from interface.widgets.assemblydisplay import AssemblyDisplay as AD
from PyQt5.QtWidgets import QGraphicsView, QGraphicsScene, QFrame, QGridLayout, \
    QLabel, QGraphicsItem
from PyQt5.QtGui import QPainterPath, QDrag, QColor
from PyQt5.QtCore import QPoint, QMimeData, Qt, pyqtSignal
import matplotlib.colors as color
import matplotlib.cm as cmx
import matplotlib.pyplot as plt
from poropy_core.src.poropy_core import Assembly


class CoreDisplay(QGraphicsView):
    
    updateSignal = pyqtSignal()

    def __init__(self, parent=None):
        super(CoreDisplay, self).__init__()
        # Sets the block up to hold Qgrpahicitems
        self.myScence = QGraphicsScene()
        self.w = self.size().width()
        self.h = self.size().height()
        self.pattern = []
        
        self.setFixedSize(self.w, self.h)
        self.myScence.setSceneRect(0, 0, self.w, self.h)
        self.fitInView(0, 0, self.w, self.h)
        self.setScene(self.myScence)
        
    def build(self, stencil, bu, core, solver):
        self.solver = solver
        self.stencil = stencil
        self.core = core
        #self.bu = [[bu[ss] if ss >= 0 else None for ss in s] for s in stencil]
        self.getColorMap()
        # grabbing the rows and columns of the data
        self.numRows = len(self.stencil)
        self.numCols = len(self.stencil[0])
        self.dx = self.w / self.numCols
        self.dy = self.h / self.numRows
        
        for i in range(self.numCols):
            for j in range(self.numRows):
                if self.stencil[i][j] < 0 or stencil[i][j] in self.pattern:
                    pass
                else:
                    self.pattern.append(self.stencil[i][j])
        
        # Creating the stencil map for the AssemblyDispaly Information
        #self.stencil = [[(i,j) for i in range(self.numCols)] for j in range(self.numRows)]
#         for i in range(self.numCols):
#             for j in range(self.numRows):
#                 self.stencil[i][j] = (i,j)
        
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
        
        # Creating a check flag to see if we are in the grid we are allowed to select or move a block too
        check = True
        if self.stencil[self.ySel][self.xSel] < 0:
            check = False
        elif self.stencil[self.yRel][self.xRel] < 0:
            check = False
        
        # If we are not in this grid we just redraw the grid
        if not check:
            self.update()
            return
        # switch the positions
        self.stencil[self.ySel][self.xSel], self.stencil[self.yRel][self.xRel] = self.stencil[self.yRel][self.xRel], self.stencil[self.ySel][self.xSel]
        
        self.pattern = []
        
        #fill pattern based on numbers being greater than zero and no duplicates
        for i in range(self.numCols):
            for j in range(self.numRows):
                if self.stencil[i][j] < 0 or self.stencil[i][j] in self.pattern:
                    pass
                else:
                    self.pattern.append(self.stencil[i][j])
        
        #giving physics new values, and recalculating
        self.core.set_pattern(self.pattern)
        
        self.update()
        self.updateSignal.emit()
        
    def getColorMap(self):
        cmap = plt.get_cmap('viridis')

        cNorm = color.Normalize(vmin=-50, vmax=50)
        self.scalarMap = cmx.ScalarMappable(norm=cNorm, cmap=cmap)

    def update(self):
        super(CoreDisplay, self).update()
        self.myScence.clear()
        for i in range(self.numCols):
            for j in range(self.numRows):
                # 
                index = self.stencil[j][i]
                power = self.solver.cycle_keff()
                if index < 0:
                    # -20 is an index that does not exist in our test cases, therefore will always be a different color
                    c = [int(mm * 255) for mm in self.scalarMap.to_rgba(-20)[:-1]]
                    ass = None
                else:
                    ass = self.core.assembly(index)
                    c = [int(mm * 255) for mm in self.scalarMap.to_rgba(ass.burnup())[:-1]]
                color = QColor(*c)
                text = self.getText(ass, power[0])
                item = AD(text, QPoint(i * self.dx, j * self.dy), self.dx, self.dy, color)
                self.scene().addItem(item)
                
    def getText(self, ass, power):
        if not ass:
            return "R"
        power = "{:6.4f}".format(power)
        return "\n".join([str(i) for i in [ass.serial_number(), ass.type(), ass.mass(), ass.burnup(), power]])
            
