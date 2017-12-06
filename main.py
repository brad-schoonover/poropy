from PyQt5.QtWidgets import QApplication
from interface.interface import MainWindow
import sys

app = QApplication(sys.argv)
#self.connections()
form = MainWindow()
form.show()
app.exec_()