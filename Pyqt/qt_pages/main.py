import sys
import os
from PyQt6.QtWidgets import *
from PyQt6.QtCore import *
from PyQt6.QtGui import QKeyEvent, QPixmap

class Carousel(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PyQt6 Image Carousel Example")

        # List of image file paths (use absolute paths or ensure the images exist)
        self.images = [
            "image1.jpg",  # Replace with actual image paths
            "image2.jpg",
            "image3.jpg",
            "image4.jpg"
        ]
        self.current_index = 0

        # Maximum size for the images
        self.max_width = 800
        self.max_height = 600

        # Create the main widget and layout
        main_widget = QWidget()
        main_layout = QVBoxLayout(main_widget)

        # Create label to display images
        self.image_label = QLabel()
        self.image_label.setAlignment(Qt.AlignmentFlag.AlignCenter)

        # Create navigation buttons
        self.btn_prev = QPushButton("Previous")
        self.btn_next = QPushButton("Next")
        self.btn_prev.clicked.connect(self.show_previous_image)
        self.btn_next.clicked.connect(self.show_next_image)
        
        # Create a horizontal layout for the buttons
        button_layout = QHBoxLayout()
        button_layout.addWidget(self.btn_prev)
        button_layout.addWidget(self.btn_next)

        # Add image label, button layout, and manual adjust button to the main layout
        main_layout.addWidget(self.image_label)
        main_layout.addLayout(button_layout)

        # Set the main widget as the central widget
        self.setCentralWidget(main_widget)

        # Load the first image
        self.update_image()
    
    def keyPressEvent(self, event: QKeyEvent) -> None:
        if event.key() == Qt.Key.Key_N:
            self.btn_next.click()
        if event.key() == Qt.Key.Key_P:
            self.btn_prev.click()

    def update_image(self):
        """Update the image shown in the label based on the current index."""
        image_path = self.images[self.current_index]
        if os.path.exists(image_path):
            pixmap = QPixmap(image_path)
            if not pixmap.isNull():
                # Scale the pixmap to fit within the max dimensions while maintaining aspect ratio
                scaled_pixmap = pixmap.scaled(
                    self.max_width, self.max_height, 
                    Qt.AspectRatioMode.KeepAspectRatio, 
                    Qt.TransformationMode.SmoothTransformation
                )
                self.image_label.setPixmap(scaled_pixmap)

                # Force the event loop to process the image changes before adjusting size
                QApplication.processEvents()

                # Adjust the window size to fit the pixmap dimensions
                self.image_label.adjustSize()  # Adjust QLabel to fit the image
                self.adjustSize()  # Adjust QMainWindow to fit everything
            else:
                self.image_label.setText("Failed to load image.")
                self.adjustSize()
        else:
            self.image_label.setText(f"File not found: {image_path}")
            self.adjustSize()

    def show_previous_image(self):
        """Show the previous image in the list."""
        self.current_index = (self.current_index - 1) % len(self.images)
        self.update_image()

    def show_next_image(self):
        """Show the next image in the list."""
        self.current_index = (self.current_index + 1) % len(self.images)
        self.update_image()

    def adjustSizeManually(self):
        """Manually adjust the size."""
        self.image_label.adjustSize()
        self.adjustSize()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = Carousel()
    window.show()
    sys.exit(app.exec())
