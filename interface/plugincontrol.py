

from PyQt5.QtWidgets import QDialog, QGroupBox, QTextEdit, QVBoxLayout, QDialogButtonBox, QHBoxLayout, QLabel, QFrame, QScrollArea, QListWidget, QSizePolicy, QStackedLayout
import os
import sys
import traceback
import warnings
import interface.widgets as widgets
from poropy_core.src.poropy_core import * 


class PluginControl(QDialog):
    """Base control dialog for using plugins defined in plugin.py"""

    def __init__(self, model, fName, parent=None):
        QDialog.__init__(self, parent)
        
        self.model = model
        self.fName = fName
        defaultHelp = """Define this help section with the set_help method of the
        PluginControl subclass.  This will be given to a QTextEdit (thus you 
        can use HTML, among other things)."""

        # ## create the initial dialog

        self.setSizeGripEnabled(True)

        # create default widgets
        self.pluginList = QListWidget()
        self.pluginList.setMaximumWidth(200)
        self.pluginList.addItem("Help")
        desc = QGroupBox('Core Builder')
        desc.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Minimum)
        self.help = QLabel(self)
        self.set_help(defaultHelp)
        # self.help.setReadOnly(True)
        dLayout = QVBoxLayout()
        dLayout.addWidget(self.help)
        desc.setLayout(dLayout)
        helpLayout = QVBoxLayout()
        helpLayout.addWidget(desc)
        defaultFrame = QFrame()
        defaultFrame.setLayout(helpLayout)
        sa = QScrollArea()
        sa.setMinimumSize(600, 600)
        saLayout = QVBoxLayout()
        saLayout.addWidget(defaultFrame)
        sa.setLayout(saLayout)
        closeButton = QDialogButtonBox(QDialogButtonBox.Close)

        # create initial layout
        self.frameLayout = QStackedLayout()
        self.frameLayout.addWidget(sa)

        rightLayout = QVBoxLayout()
        rightLayout.addLayout(self.frameLayout)
        rightLayout.addWidget(closeButton)

        mainLayout = QHBoxLayout()
        mainLayout.addWidget(self.pluginList)
        mainLayout.addLayout(rightLayout)

        self.setLayout(mainLayout)

        # self.connect(closeButton, SIGNAL("rejected()"), self.accept)
        # self.connect(self.pluginList,SIGNAL("currentRowChanged(int)"),self.frameLayout,SLOT("setCurrentIndex(int)"))

        # ## populate panels for each core plugin
        
        #sys.path.append(self.fName)  # add this util directory to python path
        # for root, dirs, files in os.walk(self.fName):
        #    print("73")
        # for f in files:
        if self.fName.endswith(".py"):
            self.fName = self.fName.split('.')[0]
            # print(fName)
            try:
                self.py_mod = __import__(str(self.fName))
                self.pluginList.addItem(self.fName)
            except ImportError:
                self.py_mod = None
                # TODO: Make traceback work
                #traceback.print_exc()
                warnings.warn("Unable to load module {0}".format(self.fName))
                
    def data(self):
        return self.py_mod

    def set_help(self, helpString):
        self.help.setText(helpString)

    def get_control_frame(self, controller):
        
        # # create frame

        frame = QFrame()
        frame.setMinimumSize(600, 600)

        frame.controllerVals = {}
        frame.controller = controller

        inputs = controller.userInputs()
        actions = controller.runActions()
        description = controller.description()

        # # create description

        desc = QGroupBox('Description')
        dLayout = QVBoxLayout()
        dd = QTextEdit(description)
        dd.setReadOnly(True)
        dd.setMaximumHeight(75)
        dLayout.addWidget(dd)
        desc.setLayout(dLayout)

        # # create input fields

        ins = QGroupBox('Inputs')
        groupLayout = QVBoxLayout()
        for var, varDict in inputs:
            typ = varDict['type']
            itemLayout = QHBoxLayout()
            if typ == "openpath":
                itemLayout.addWidget(QLabel(varDict['label']))
                frame.controllerVals[var] = {}
                frame.controllerVals[var]['widget'] = widgets.FileChooser()
                frame.controllerVals[var]['ret'] = lambda widget: str(widget.getText())
                if 'default' in varDict:
                    frame.controllerVals[var]['widget'].setText(varDict['default'])
                itemLayout.addWidget(frame.controllerVals[var]['widget'])
            elif typ == "savepath":
                itemLayout.addWidget(QLabel(varDict['label']))
                frame.controllerVals[var] = {}
                frame.controllerVals[var]['widget'] = widgets.FileChooser(save=True)
                frame.controllerVals[var]['ret'] = lambda widget: str(widget.getText())
                if 'default' in varDict:
                    frame.controllerVals[var]['widget'].setText(varDict['default'])
                itemLayout.addWidget(frame.controllerVals[var]['widget'])
            elif typ == "dir":
                itemLayout.addWidget(QLabel(varDict['label']))
                frame.controllerVals[var] = {}
                frame.controllerVals[var]['widget'] = widgets.FileChooser(directory=True)
                frame.controllerVals[var]['ret'] = lambda widget: str(widget.getText())
                if 'default' in varDict:
                    frame.controllerVals[var]['widget'].setText(varDict['default'])
                itemLayout.addWidget(frame.controllerVals[var]['widget'])
            elif typ == "checkbox":
                itemLayout.addWidget(QLabel(varDict['label']))
                frame.controllerVals[var] = {}
                frame.controllerVals[var]['widget'] = QCheckBox()
                frame.controllerVals[var]['ret'] = lambda widget: widget.isChecked()
                itemLayout.addWidget(frame.controllerVals[var]['widget'])
            elif typ == "freetext":
                itemLayout.addWidget(QLabel(varDict['label']))
                frame.controllerVals[var] = {}
                frame.controllerVals[var]['widget'] = QLineEdit()
                frame.controllerVals[var]['ret'] = lambda widget: str(widget.text())
                if 'default' in varDict:
                    frame.controllerVals[var]['widget'].setText(str(varDict['default']))
                itemLayout.addWidget(frame.controllerVals[var]['widget'])
            elif typ == "linktext":
                itemLayout.addWidget(QLabel(varDict['label']))
                frame.controllerVals[var] = {}
                frame.controllerVals[var]['widget'] = widgets.LinkText(var)
                frame.controllerVals[var]['ret'] = lambda widget: str(widget.text())
                if 'default' in varDict:
                    frame.controllerVals[var]['widget'].setText(varDict['default'])
                itemLayout.addWidget(frame.controllerVals[var]['widget'])
            else:
                warnings.warn("Skipping unknown widget type: {0}".format(var))
            groupLayout.addLayout(itemLayout)
        ins.setLayout(groupLayout)

        # # create action buttons

        acts = QGroupBox('Actions')
        groupLayout = QVBoxLayout()
        for func, funcDict in actions:
            itemLayout = QHBoxLayout()
            btn = widgets.ProgressBarButton(funcDict['label'], controller, func, parent=self.model)
            funcDesc = QLabel(funcDict['description'])
            self.connect(btn, SIGNAL("pressed()"), self.resolve_frame)
            self.connect(btn, SIGNAL("released()"), btn.progressBarRun)
            itemLayout.addWidget(btn)
            itemLayout.addWidget(funcDesc)
            groupLayout.addLayout(itemLayout)    
        acts.setLayout(groupLayout)

        # # set frame layouts
        inFrame = QFrame()
        inFrame.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
        inLayout = QVBoxLayout()
        inLayout.addWidget(desc)
        inLayout.addWidget(ins)
        inLayout.addWidget(acts)
        inFrame.setLayout(inLayout)
        sa = QScrollArea()
        sa.setWidget(inFrame)
        sa.setWidgetResizable(True)
        outlayout = QVBoxLayout()
        outlayout.addWidget(sa)
        frame.setLayout(outlayout)

        return frame

    def resolve_frame(self):
        """Slot for all frame action buttons

            Sends input values to current frame's controller

        """

        frame = self.frameLayout.currentWidget()
        for var, varDict in list(frame.controllerVals.items()):
            setattr(frame.controller, var, varDict['ret'](varDict['widget']))
