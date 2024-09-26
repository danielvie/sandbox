import sys

import threading
from time import sleep
from PyQt6.QtCore import Qt, pyqtSignal, QObject, QThread, QRunnable, pyqtSlot, QThreadPool
from PyQt6.QtWidgets import QWidget, QApplication, QVBoxLayout, QPushButton, QLabel

        
class Signals(QObject):
    status = pyqtSignal(str)
    started = pyqtSignal()
    finished = pyqtSignal()

class Worker(QRunnable):
    def __init__(self, fun) -> None:
        super().__init__()
        self.fun = fun
        self.signals = Signals()
        
    @pyqtSlot()
    def run(self):
        self.signals.started.emit()
        self.fun()
        self.signals.finished.emit()


class Window(QWidget):
    
    def __init__(self) -> None:
        super().__init__()
        
        self.signals = Signals()
        self.thread_pool = QThreadPool()
        self.setMinimumSize(300, 200)
        
        layout = QVBoxLayout()
        layout.setAlignment(Qt.AlignmentFlag.AlignBottom)
        
        self.status = QLabel("...")
        self.btn_play = QPushButton("play")
        self.btn_foo = QPushButton("foo")

        layout.addWidget(self.status)
        layout.addWidget(self.btn_play)
        layout.addWidget(self.btn_foo)
        
        self.setLayout(layout)
        
        self.btn_play.clicked.connect(self.play)
        self.btn_foo.clicked.connect(self.foo)
        
        self.signals.status.connect(lambda x: self.status.setText(x))

    def play(self):
        print('play')

    def foo_helper(self):
        print('foo [in]')
        print('foo')
        sleep(15)
        print('foo [out]')
        self.signals.status.emit('i have finished')

    def foo(self):
        worker = Worker(self.foo_helper)
        worker.signals.started.connect(lambda: print(f'iiiii have started ({self.thread_pool.activeThreadCount()})'))
        worker.signals.finished.connect(self.on_finish)

        self.thread_pool.start(worker)
        self.signals.status.emit('foo started')
    def on_finish(self):
        with threading.Lock():
            print(f'i have finished ({self.thread_pool.activeThreadCount()})')

if __name__ == "__main__":
    print('asdfasdfa')
    
    app = QApplication([])
    window = Window()
    
    window.show()
    
    sys.exit(app.exec())