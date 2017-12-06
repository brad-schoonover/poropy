from PyQt5.QtWidgets import QWidget, QHBoxLayout
import datetime
from interface.graph import Chart
#import pyqtgraph as pg
import sys


class PlotWidget(Chart):
    def __init__(self):
        super(PlotWidget,self).__init__()
        
