from PyQt5.QtGui import QPen, QPainter, QColor, QBrush
from PyQt5.QtCore import Qt, QRectF, QPointF
from PyQt5.QtWidgets import QGraphicsItem, QLabel, QGridLayout, QGraphicsTextItem

class AssemblyDisplay(QGraphicsItem):
    def __init__(self, text=None, pos=None, w=None, h=None, indicator=None, burnUp=None, color=None):
        super(AssemblyDisplay, self).__init__()
        self.indicator = indicator
        self.burnUp = burnUp
        self.w = w
        self.h = h
        self.text = text
        self._brush = QBrush(Qt.black)
        self.color = color
        #dragenterevent
        self.setPosition(pos)
        self.setFlags((QGraphicsItem.ItemIsMovable|QGraphicsItem.ItemIsSelectable))
        self.make_labels()
        
    def make_labels(self):
        label = QGraphicsTextItem(parent=self)
        label.setPlainText(self.text)
    
    def boundingRect(self):
        return QRectF(0, 0, self.w, self.h)
    
    def setBrush(self, brush):
        self._brush = brush
        self.update()
    
    def paint(self, painter, option, widget):
        painter.setPen(Qt.black)
        painter.drawRect(self.boundingRect())
        self._brush = QBrush(self.color)
        painter.fillRect(self.boundingRect(), self._brush)
            
    def setPosition(self, pos):
        self.setPos(self.mapFromParent(QPointF(pos)))
        
