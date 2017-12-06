from PyQt5.QtWidgets import QGraphicsView, QGraphicsItem, QGraphicsScene, QAction, QApplication
from PyQt5.QtCore import QObject, QMimeData, QMutex, Qt, QTimer
from PyQt5.QtGui import QImage, QPainter, QPixmap, QPainterPath, QDrag, QColor
from interface.widgets.assemblydisplay import AssemblyDisplay

L = 100  # default pixel width of assembly displays


class CoreDisplay(QGraphicsView):

    def __init__(self, reactor, parent=None):
        QGraphicsView.__init__(self, parent)
        
        if reactor == None:
            self.core = None
        else:
            self.core = reactor.core

        self.coloring = 0

        self.needsRefresh = True

        self.mutex = QMutex()

        self.scene = QGraphicsScene(self)
        self.scene.maxZ = 0
        self.setScene(self.scene)

        self.setHorizontalScrollBarPolicy(Qt.ScrollBarAlwaysOff)
        self.setVerticalScrollBarPolicy(Qt.ScrollBarAlwaysOff)

        #self.draw_core()

        timer = QTimer(self)

        timer.start(10)
        
        #creating an action for swamping
        self.assembly_swap_action = QAction("Action", self)

    def set_coloring(self, coloring):
        self.coloring = coloring

    def set_core(self, core):
        self.core = core
        self.needsRefresh = True

    def pattern_updated(self):
        self.needsRefresh = True

    def resizeEvent(self, event):
        self.fitInView(self.scene.sceneRect(), Qt.KeepAspectRatio)

    def refresh(self):
        try:
            for item in list(self.scene.items()):
                if isinstance(item, AssemblyDisplay):
                    item.refresh()
        except RuntimeError: pass

    def draw_core(self, stencil, assemblies, power):
        self.stencil = stencil
        self.assemblies = assemblies
        self.pattern = self.core.pattern()
        if not self.needsRefresh: return

        if not self.core: return

        self.mutex.lock()

        self.needsRefresh = False

        self.scene.clear()

        # map positions onto (row,col) for easier plotting
        mapped_pattern_ids = {}
        i = 0
        for r, row in enumerate(self.stencil):
            for c, assType in enumerate(row):
                if r != 0 and c == 0:  # if on reflected surface
                    mapped_pattern_ids[r, c] = mapped_pattern_ids[0, r]
                elif assType != -1:
                    mapped_pattern_ids[r, c] = self.pattern[i]
                    i += 1
                else:
                    mapped_pattern_ids[r, c] = -1  # reflector

        numRows = len(self.stencil)
        numCols = len(self.stencil[0])

        peaks = []

        i = 0
        for r, row in enumerate(self.stencil):
            for c, assType in enumerate(row):
                patt_id = mapped_pattern_ids[r, c]
                if r != 0 and c == 0:  # if on reflected surface
                    a = self.assemblies[patt_id]
                    if patt_id == -1:
                        a.name = "R"
                        type_ = "reflector"
                    else:
                        a.name = patt_id
                        type_ = "reflected surface"
                    ass = AssemblyDisplay(r, c, a, type_, self, scene=self.scene,
                                          coloring=self.coloring)
                    peaks.append((power[i], ass))

#                 else:
#   
#                     if patt_id == -1:
#                         a = self.core.reflector
#                         a.name = "R"
#                         ass = AssemblyDisplay(r, c, a, "reflector", self,
#                                               scene=self.scene,
#                                               coloring=self.coloring)
#                         peaks.append((power[i], ass))
#                     else:
#                         a = self.assemblies[patt_id]
#                         a.name = patt_id
#                         ass = AssemblyDisplay(r, c, a, "fuel", self,
#                                               scene=self.scene,
#                                               coloring=self.coloring)
#                         peaks.append((power[i], ass))
                        #i += 1
                        
        maxPeaker = peaks[1]
        #maxPeaker.set_coloring(max_peak=True)

        m = 20  # pixel margin
        self.scene.setSceneRect(-m, -m, numCols * L + 2 * m, numRows * L + 2 * m)
        print("CoreDisplay, draw_core 132")
        self.fitInView(self.scene.sceneRect(), Qt.KeepAspectRatio)

        self.mutex.unlock()
        print("hello")
        #trigger = pyqtSignal()
        
    def assembly_swap(self, toFrom):
        pass

    def save_image(self, fname):
      img = QImage(self.scene.width(), self.scene.height(), QImage.Format_ARGB32_Premultiplied)
      p = QPainter(img)
      self.scene.render(p)
      p.end()
      img.save(fname)
      

class SignalFire(QObject):

    def __init__(self, parent=None):
        QAction.__init__(self, parent)

    def fireSwap(self, to, from_):
        pass
        
if __name__ == "__main__":
    import sys
    app = QApplication(sys.argv)
    form = CoreDisplay(None)
    form.show()
    app.exec_()

