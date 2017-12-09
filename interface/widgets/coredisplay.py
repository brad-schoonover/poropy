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
        self.num_rows = len(stencil)
        self.num_cols = len(stencil[0])
        self.dx = self.w / self.num_cols
        self.dy = self.h / self.num_rows
        
        self.items = []
        for i in range(self.num_cols):
            sub_items = []
            for j in range(self.num_rows):
                # Creates the individual class and puts into a list, of AssemblyDispaly
                item = AD("hello{}{}".format(i, j), QPoint(i * self.dx, j * self.dy), self.dx, self.dy)
                sub_items.append(item)
                self.scene().addItem(sub_items[j])
            # Creates List of list
            self.items.append(sub_items)
            
    def mouseMoveEvent(self, event):
        # Creataing a new mouse event with old functionallity, along with new
        super(CoreDisplay, self).mouseMoveEvent(event)
            
    def mousePressEvent(self, event):
        # Creataing a new mouse event with old functionallity, along with new
        super(CoreDisplay, self).mousePressEvent(event)
        # block location
        self.xSelected = int(event.pos().x() / self.w * (self.num_cols))
        self.ySelected = int(event.pos().y() / self.h * (self.num_rows))
        
    def mouseReleaseEvent(self, event):
        # Creataing a new mouse event with old functionallity, along with new
        super(CoreDisplay, self).mouseReleaseEvent(event)
        # grabs the postition in the list for held
        
        # grabs the postition in the list for groud item
