from PyQt5.QtWidgets import QGraphicsItem, QGraphicsTextItem, QGraphicsScene
from PyQt5.QtGui import QImage, QPainter, QPixmap, QPainterPath, QDrag, QColor, QPolygonF
from PyQt5.QtCore import QPointF, QRectF, Qt

COLOR_BURNUP = 0
COLOR_ENRICHMENT = 1
COLOR_POWER = 2
COLOR_KINF = 3

L = 100

class AssemblyDisplay(QGraphicsItem):
    
    

    def __init__(self, r, c, ass, type_, view, parent=None, scene=None, coloring=None,
                 max_peak=False):
        super(AssemblyDisplay, self).__init__()
        
        self.loc = [r, c]
        self.assembly = ass
        self.type = type_
        self.view = view
        self.scene = QGraphicsScene()
        #self.sigFire = SignalFire()

        self.coloring = coloring

        self.set_coloring(max_peak=max_peak)

        self.draw_item()

    def set_coloring(self, max_peak=False):
    
        if self.type == "fuel" or self.type == "reflected surface":
        
            if self.coloring == COLOR_ENRICHMENT:
                r = 4
                rc = 6.0
            elif self.coloring == COLOR_POWER:
                if max_peak:
                    self.defaultColor = Qt.magenta
                    return
                r = self.assembly.peak
                rc = 2.0
            elif self.coloring == COLOR_BURNUP:
                r = 1 * self.assembly.burnup()
                rc = 50.0
            elif self.coloring == COLOR_KINF:
                r = 2.0 * (1.0 - 0.75)
                rc = 1.5

            if r >= rc:
                self.defaultColor = Qt.red
            else:
                self.defaultColor = QColor(r / rc * 255, (rc - r) / rc * 255, 0)

            if self.type == "fuel":
                self.setFlags(QGraphicsItem.ItemIsSelectable)
                self.setAcceptHoverEvents(True)
                self.setAcceptDrops(True)

        elif self.type == "reflector":
            self.defaultColor = Qt.cyan
        else:
            self.defaultColor = Qt.white

    def draw_item(self):

        print("draw_item, assemblydispaly, 70")
        self.color = self.defaultColor
        self.path = QPainterPath()
        points = [(0, 0), (0, L), (L, L), (L, 0)]
        self.path.addPolygon(QPolygonF([QPointF(x, y) for x, y in points]))
        self.path.closeSubpath()
        self.make_labels()
        self.moveBy(self.loc[1] * L, self.loc[0] * L)

        #s = self.get_scale()
        s = 1
        self.pixmap = QPixmap(L * s, L * s)
        self.pixpainter = QPainter(self.pixmap)
        rect = self.boundingRect()
        rect.translate(self.loc[1] * L, self.loc[0] * L)
        self.view.setScene(self.scene)
        #self.scene.render(self.pixpainter)

    def make_labels(self):
        id_ = QGraphicsTextItem(parent=self)

        f1 = self.assembly.name
        f2 = ""
        f3 = ""
        f4 = ""
        f5 = ""
        f6 = ""
        if self.type == "fuel" or self.type == "reflected surface":
            f2 = "FIX ME"
#            if self.coloring == CoreDisplay.COLOR_BURNUP:
#                f3 = self.assembly.burnup
#            elif self.coloring == CoreDisplay.COLOR_ENRICHMENT:
#                f3 = self.assembly.enrichment
#            elif self.coloring == CoreDisplay.COLOR_POWER:
#                f3 = self.assembly.peak
#            f3 = "%.4f" % f3
            # TODO FIX HARD CODED NUMBERS
            f3 = "%.4f" % 4
            f4 = "%.4f" % self.assembly.burnup()
            f5 = "%.4f" % 0.0
            f6 = "%.4f" % 1.0
        text = '<p style="font-size:12px">'
        text += "<center>{0}<\center>".format(f1)
        text += "<center>{0}</center>".format(f2)
        text += "<center>{0}</center>".format(f3)
        text += "<center>{0}</center>".format(f4)
        text += "<center>{0}</center>".format(f5)
        text += "<center>{0}</center>".format(f6)
        text += '</p>'
        id_.setHtml(text)
        id_.setTextWidth(L)
        

#     def get_scale(self):
#         self.scene.size.height()
#         self.view.size.height()
#         sy = self.view.size.height() / self.sceneRect.size.height()
#         sx = self.view.size.width() / self.scene.width()
#         return min([sx, sy])

    def boundingRect(self):
        return self.path.boundingRect()

    def shape(self):
        return self.path

    def paint(self, painter, option, widget=None):
        painter.setPen(Qt.black)
        painter.setBrush(QBrush(self.color))
        painter.drawPath(self.path)

    def refresh(self):
        if self.isSelected():
            self.color = Qt.red
        else:
            self.color = self.defaultColor
        self.update()

    def hoverLeaveEvent(self, event):
        self.refresh()

    def hoverEnterEvent(self, event):
        self.color = Qt.gray
        self.update()

    def dragEnterEvent(self, event):

        if event.mimeData().assembly == self: return
        self.color = Qt.magenta
        self.update()

    def dragLeaveEvent(self, event):
        self.color = self.defaultColor
        self.update()

    def dropEvent(self, event):
        from_ = event.mimeData().assembly.loc
        to = self.loc
        if from_ != to:
            self.sigFire.fireSwap(to, from_)

    def mousePressEvent(self, event):
        if not self.type == "fuel": return

        for item in self.scene().selectedItems():
            item.setSelected(False)
        self.setSelected(True)

    def mouseMoveEvent(self, event):
        if not self.type == "fuel": return

        drag = QDrag(event.widget())
        mime = QMimeData()
        mime.assembly = self
        drag.setMimeData(mime)
        #s = self.get_scale()
        s = 1
        drag.setPixmap(self.pixmap.scaledToWidth(L * s))
        drag.setHotSpot(QPoint(event.pos().x() * s, event.pos().y() * s))
        drag.start()

    def mouseReleaseEvent(self, event):
        if not self.type == "fuel": return

