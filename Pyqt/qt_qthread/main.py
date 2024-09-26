from PyQt6.QtCore import QThread, pyqtSignal, QObject
from PyQt6.QtWidgets import QApplication, QLabel, QPushButton, QVBoxLayout, QWidget
import time
import threading

class Signals(QObject):
    update_status = pyqtSignal(str)

class FileLoaderThread(QThread):
    def __init__(self, signals):
        super().__init__()
        self.signals = signals

    def run(self):
        for i in range(5):
            time.sleep(1)
            self.signals.update_status.emit(f"Loading... {i + 1}/5")
        self.signals.update_status.emit(f"file loading completed!")

class Bla:
    def __init__(self, name = '') -> None:
        self.name = name
        print(f'{self.name} - [in]')
    def __del__(self):
        print(f'{self.name} - [out]')

        
class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.signals = Signals()
        self.threads: list[QThread] = []

        self.setMinimumSize(400, 200)
        self.status = QLabel("Press button to load file")
        self.btn_load = QPushButton("Load File")
        self.btn_play = QPushButton("Play")
        self.cont = 0

        layout = QVBoxLayout()
        layout.addWidget(self.status)
        layout.addWidget(self.btn_load)
        layout.addWidget(self.btn_play)
        self.setLayout(layout)

        self.btn_load.clicked.connect(self.load_file)
        self.btn_play.clicked.connect(self.play)
        self.signals.update_status.connect(self.update_status)
        
    def update_status(self, text: str):
        _ = Bla('update_status')
        with threading.Lock():
            self.status.setText(text)
        
    def play(self):
        _ = Bla('play')
        self.cont += 1
        print(f'pressed `play`: {self.cont}; len(threads): {len(self.threads)}')

    def load_file(self):
        _ = Bla('load_file')
        thread = FileLoaderThread(self.signals)
        self.threads.append(thread)
        thread.finished.connect(lambda: self.cleanup_thread(thread))
        thread.start()
    
    def cleanup_thread(self, thread):
        _ = Bla('cleanup_thread')
        self.threads.remove(thread)

    def on_file_loaded(self, content):
        _ = Bla('on_file_loaded')
        self.status.setText(content)

def foo():
    _ = Bla('foo')

if __name__ == "__main__":
    foo()
    app = QApplication([])
    window = MainWindow()
    window.show()
    app.exec()
