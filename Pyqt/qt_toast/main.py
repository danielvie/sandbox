import sys
from PyQt6.QtWidgets import QApplication, QLabel, QPushButton, QVBoxLayout, QWidget
from PyQt6.QtCore import Qt, QTimer

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Toast Example")
        self.setMinimumSize(300, 100)

        # Create a button
        self.button = QPushButton("Show Toast", self)
        self.button.clicked.connect(self.show_toast)

        # Create a toast label
        self.toast_label = QLabel(self)
        self.toast_label.setStyleSheet("background-color: #6b0a40; color: white; padding: 10px; border-radius: 5px; font-size: 15px")
        self.toast_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self.toast_label.setMinimumHeight(100)

        self.toast_label.hide()  # Initially hidden

        # Layout
        layout = QVBoxLayout(self)
        layout.addWidget(self.button)
        layout.addWidget(self.toast_label)
        self.setLayout(layout)

    def show_toast(self):
        # Set the message and show the toast
        self.toast_label.setText("This is a toast message")
        self.toast_label.adjustSize()
        self.toast_label.move((self.width() - self.toast_label.width()) // 2, 
                              self.button.y() + self.button.height() + 10)  # Position below the button
        self.toast_label.show()


        # Timer to hide the toast after 3 seconds
        QTimer.singleShot(10000, self.hide_toast)
        QApplication.processEvents()
        self.adjustSize()

    def hide_toast(self):
        self.toast_label.hide()
        QApplication.processEvents()
        self.adjustSize()


# Example usage
if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
