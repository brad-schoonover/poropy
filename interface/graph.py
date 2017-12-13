import matplotlib
from numpy import linspace
matplotlib.use("Qt5Agg")
from PyQt5.QtWidgets import QSizePolicy
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
from matplotlib.font_manager import FontProperties

fontP = FontProperties()
fontP.set_size('small')


class Chart(FigureCanvas):
    """Ultimately, this is a QWidget (as well as a FigureCanvasAgg, etc.)."""

    def __init__(self, axisLim=None, data=None, parent=None, width=10, height=10, dpi=100, legend=None, xlabel=None, ylabel=None, temp=False):
        fig = Figure(figsize=(width, height), dpi=dpi)
        self.axes = fig.add_subplot(111)
        fig.subplots_adjust(bottom=0.2, left=0.25)
        FigureCanvas.__init__(self, fig)
        # We want the axes cleared every time plot() is called
        self.axes.hold(False)

        # self.compute_initial_figure(axisLim, data, legend, xlabel, ylabel, temp)

        self.setParent(parent)
        FigureCanvas.setSizePolicy(self, QSizePolicy.Ignored, QSizePolicy.Ignored)
        FigureCanvas.updateGeometry(self)
        
        self.compute_initial_figure(axisLim, data, legend, xlabel, ylabel, temp)
        self.draw()

        # self.update_figure(data)

    def compute_initial_figure(self, axisLim, ys, legend, xlabel, ylabel, temp):
        self.lines = self.axes.plot(range(len(ys)), ys, 'b-', 0, ys[-1], "ro")
        self.axes.set_xlim(axisLim[:2])
        self.axes.set_ylim(axisLim[2:])
        self.axes.set_xticks(linspace(axisLim[0], axisLim[1], 3))

        # Add a legend if provided
        if legend is not None:
            self.axes.legend(legend, loc='lower center', bbox_to_anchor=(0.5, 0.05), prop=fontP, fancybox=True, shadow=True)

        # Add labels if provided
        if xlabel is not None:
            self.axes.set_xlabel(xlabel)
        if ylabel is not None:
            self.axes.set_ylabel(ylabel)

    # Creating graphs
    def updateFigure(self, data):
        dy = 0.001
        self.lines[0].set_ydata(data)
        self.axes.set_ylim([min(data) - dy, max(data) + dy])
        l = len(data)
        self.axes.set_xlim([0, l])
        self.axes.set_xticks(range(l))
        self.lines[0].set_xdata(range(l))
        self.lines[1].set_ydata(data[-1])
        self.lines[1].set_xdata(l - 1)
        self.draw()
        # self.draw()
