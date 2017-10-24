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

        #self.compute_initial_figure(axisLim, data, legend, xlabel, ylabel, temp)

        self.setParent(parent)
        FigureCanvas.setSizePolicy(self, QSizePolicy.Ignored, QSizePolicy.Ignored)
        FigureCanvas.updateGeometry(self)

        self.draw()

        #self.update_figure(data)

    def compute_initial_figure(self, axisLim, ys, legend, xlabel, ylabel, temp):
        c = ['r-', 'g-', 'b-', 'y-']
        d = []
        for i, y in enumerate(ys):
            d.append(linspace(axisLim[0], axisLim[1], len(y)))
            d.append(y)
            d.append(c[i])
        self.lines = self.axes.plot(*d)
        self.axes.set_xlim(axisLim[:2])
        self.axes.set_ylim([0, 100])
        self.axes.set_xticks(linspace(axisLim[0], axisLim[1], 3))
        if temp:
            self.axes.set_yticklabels(linspace(axisLim[2], axisLim[3], 6).astype(int))
        else:
            self.axes.set_yticks(linspace(axisLim[2], axisLim[3], 6))

        # Add a legend if provided
        if legend is not None:
            self.axes.legend(legend, loc='lower center', bbox_to_anchor=(0.5, 0.05), prop=fontP, fancybox=True, shadow=True)

        # Add labels if provided
        if xlabel is not None:
            self.axes.set_xlabel(xlabel)
        if ylabel is not None:
            self.axes.set_ylabel(ylabel)

    # Creating graphs
    def update_figure(self, data):
        for i, d in enumerate(data):
            self.lines[i].set_ydata(d)
            self.axes.redraw_in_frame()
            self.blit(self.axes.bbox)
        # self.draw()
