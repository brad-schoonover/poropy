from interface.widgets.assemblydisplay import AssemblyDisplay as AD
from PyQt5.QtWidgets import QGraphicsView, QGraphicsScene, QFrame, QGridLayout,\
    QLabel
from PyQt5.QtGui import QPainterPath
from PyQt5.QtCore import QPoint

class CoreDisplay(QGraphicsView):
    def __init__(self, parent=None):
        super(CoreDisplay, self).__init__()
#         self.view = QGraphicsScene()
        self.setScene(QGraphicsScene())
        self.path = QPainterPath()
        self.w = self.size().width()
        self.h = self.size().height()
        
    def build(self, stencil):
        num_rows = len(stencil)
        num_cols = len(stencil[0])
        self.items = []
        for i in range(num_cols):
            sub_items = []
            for j in range(num_rows):
                item = AD("hello{}{}".format(i, j), QPoint(i*75, j*75), self.w, self.h)
                sub_items.append(item)
                self.scene().addItem(sub_items[j])
            self.items.append(sub_items)
#         self.item = AD("hello", QPoint(0,0), self.w, self.h)
#         self.item2 = AD("hello", QPoint(0,20), self.w, self.h)
#         self.scene().addItem(self.item)
#         self.scene().addItem(self.item2)