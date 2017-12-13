from PyQt5.QtWidgets import QWidget, QTreeWidget, QHBoxLayout, QTreeWidgetItem
from PyQt5.QtCore import QStringListModel
import copy


class PatternList(QWidget):
    def __init__(self,parent=None):
        QWidget.__init__(self,parent)

        headers = ["Maxpeak","keff","Objective","Pattern"]
        self.numCols = 4

        self.display = QTreeWidget()
        self.display.setSortingEnabled(True)
        self.display.setColumnCount(self.numCols)
        self.display.setHeaderLabels(headers)
        l = QHBoxLayout()
        l.addWidget(self.display)
        self.setLayout(l)

    #def checkbox_clicked(self,item,col):
    #    if col != 4: return
    #    if item.checkState(col) == Qt.Checked:
    #        self.emit(SIGNAL("saveItem(QTreeWidgetItem*)"),item)
    #    else:
    #        self.emit(SIGNAL("unsaveItem(QTreeWidgetItem*)"),item)
    #
    #def add_item(self,item):
    #    self.display.addTopLevelItem(item)

    #def remove_item(self,item):
    #    self.display.removeItemWidget(item,0)


    def add_pattern(self,i,pattern,keff,maxpeak,objective):
        text = [str(i) for i in [maxpeak, keff, objective, pattern]]
        item = QTreeWidgetItem(self.display,text)
        #item.setCheckState(4,Qt.Unchecked)
        item.setData(0,32,i)

    def resize(self):
        for c in range(self.numCols):
            self.display.resizeColumnToContents(c)

    def change_pattern(self):
        try:
          data = self.display.selectedItems()[0].data(0,32)
        except IndexError: pass # selection was changed to nothing
        
    def clear(self):
        self.display.clear()
