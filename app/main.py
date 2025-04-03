# app/main.py
import sys
from PyQt5.QtWidgets import QApplication
from mainwindow import MainWindow


module_path = r"D:\\cpp proj\\PATD\\laba2.1\\build\\Release"
if module_path not in sys.path:
    sys.path.append(module_path)
    

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MainWindow()
    win.show()
    sys.exit(app.exec_())


