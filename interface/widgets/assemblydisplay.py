from PyQt5.QtGui import QPen, QPainter, QColor
from PyQt5.QtCore import Qt, QRectF, QPointF
from PyQt5.QtWidgets import QGraphicsItem, QLabel, QGridLayout, QGraphicsTextItem

class AssemblyDisplay(QGraphicsItem):
    def __init__(self, text=None, pos=None, w=None, h=None):
        super(AssemblyDisplay, self).__init__()
        self.w = w
        self.h = h
        self.text = text
        #dragenterevent
        self.setPos(self.mapFromParent(QPointF(pos)))
        self.pos = pos
        self.setFlags((QGraphicsItem.ItemIsMovable|QGraphicsItem.ItemIsSelectable))
        self.make_labels(text)
        
    def make_labels(self, text):
        label = QGraphicsTextItem(parent=self)
        label.setPlainText(self.text)
    
    def boundingRect(self):
        return QRectF(0, 0, self.w, self.h)
    
    def paint(self, painter, option, widget):
        painter.setPen(Qt.black)
        painter.drawRect(self.boundingRect())
        
    def position(self):
        return self.pos