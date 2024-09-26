import sys
import time
from PyQt6.QtCore import *
from PyQt6.QtWidgets import *
from PyQt6.QtWidgets import QWidget

class WorkerSignals(QObject):
    started = pyqtSignal()
    finished = pyqtSignal()

class Worker(QRunnable):
    def __init__(self, fun) -> None:
        super().__init__()
        self.fun = fun
        self.signals = WorkerSignals()
        
    def run(self):
        self.signals.started.emit()
        self.fun()
        self.signals.finished.emit()

class Window(QWidget):
    def __init__(self) -> None:
        super().__init__()
        
        self.threadpool = QThreadPool()

        self.setMinimumSize(300, 200)

        layout = QVBoxLayout()
        
        self.status = QLabel('...')
        self.btn_play = QPushButton('Play')
        self.btn_foo = QPushButton('Foo')
        
        # Set button styles
        self.btn_play.setStyleSheet("""
        QPushButton {
            background-color: #0284c7;
            height: 50px;
        }
        QPushButton:hover {
            background-color: #075985;
        }
        QPushButton:pressed {
            background-color: #075985;
            color: gray;
            height: 50px; /* Keep height consistent */
        }
        """)

        layout.addWidget(self.status)
        layout.addWidget(self.btn_play)
        layout.addWidget(self.btn_foo)
        
        self.setLayout(layout)
        
        # Connect play and foo buttons
        self.btn_play.clicked.connect(self.animate_button)  # Connect animation to the button
        self.btn_play.clicked.connect(self.play)
        self.btn_foo.clicked.connect(self.foo)

    def play(self):
        print('Play button clicked')
        
    def foo_helper(self):
        print('Foo button clicked')
        time.sleep(3)
        
    def foo(self):
        worker = Worker(self.foo_helper)
        worker.signals.finished.connect(lambda: print("I have finished!"))
        self.threadpool.start(worker)

if __name__ == "__main__":
    app = QApplication([])
    window = Window()
    window.show()

    sys.exit(app.exec())
