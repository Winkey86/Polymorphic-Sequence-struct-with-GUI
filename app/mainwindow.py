from PyQt5.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QTableWidget, QTableWidgetItem,
    QPushButton, QInputDialog, QMessageBox, QLineEdit, QDialog, QFormLayout,
    QComboBox, QLabel, QHeaderView
)
from PyQt5.QtCore import Qt
import sequences 

class CreateDialog(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Make a sequence")
        self.name_edit = QLineEdit()
        self.struct_combo = QComboBox()
        self.struct_combo.addItems(["ARRAY", "LIST"])
        self.data_type_label = QLabel("INT")
        self.mutability_combo = QComboBox()
        self.mutability_combo.addItems(["MUTABLE", "IMMUTABLE"])
        self.elements_edit = QLineEdit()

        layout = QFormLayout()
        layout.addRow("Name:", self.name_edit)
        layout.addRow("Base struct:", self.struct_combo)
        layout.addRow("DataType:", self.data_type_label)
        layout.addRow("Mutability:", self.mutability_combo)
        layout.addRow("Content (space):", self.elements_edit)

        self.create_button = QPushButton("Create")
        self.create_button.clicked.connect(self.accept)
        layout.addWidget(self.create_button)

        self.setLayout(layout)

    def get_values(self):
        name = self.name_edit.text().strip()
        struct_type = self.struct_combo.currentText()
        mutability = self.mutability_combo.currentText()

        elements_text = self.elements_edit.text().strip()
        elements = []
        if elements_text:
            try:
                elements = [int(x) for x in elements_text.split()]
            except ValueError:
                QMessageBox.warning(self, "ERROR", "WRONG FORMAT OF ELEMENTS")
        return name, struct_type, "INT", mutability, elements

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Graphic User Interface for Sequences")
        self.sequences_dict = {} 

        self.table = QTableWidget(0, 6)
        self.table.setHorizontalHeaderLabels(
            ["Name", "StructType", "DataType", "Mutability", "Length", "Content"]
        )
        self.table.setSelectionBehavior(self.table.SelectRows)
        self.table.setSelectionMode(self.table.SingleSelection)
        self.table.horizontalHeader().setSectionResizeMode(0, QHeaderView.Interactive)
        self.table.setColumnWidth(0, 250)
        self.table.horizontalHeader().setSectionResizeMode(5, QHeaderView.Stretch)

        self.btn_create = QPushButton("Create")
        self.btn_select = QPushButton("Select")
        self.btn_delete = QPushButton("Delete")
        self.btn_append = QPushButton("Append")
        self.btn_prepend = QPushButton("Prepend")
        self.btn_insert = QPushButton("InsertAt")
        self.btn_concat = QPushButton("Concat")

        self.btn_create.clicked.connect(self.create_sequence)
        self.btn_select.clicked.connect(self.select_sequence)
        self.btn_delete.clicked.connect(self.delete_sequence)
        self.btn_append.clicked.connect(self.append_value)
        self.btn_prepend.clicked.connect(self.prepend_value)
        self.btn_insert.clicked.connect(self.insert_value)
        self.btn_concat.clicked.connect(self.concat_sequence)

        btn_layout = QHBoxLayout()
        btn_layout.addWidget(self.btn_create)
        btn_layout.addWidget(self.btn_select)
        btn_layout.addWidget(self.btn_delete)
        btn_layout.addWidget(self.btn_append)
        btn_layout.addWidget(self.btn_prepend)
        btn_layout.addWidget(self.btn_insert)
        btn_layout.addWidget(self.btn_concat)

        main_layout = QVBoxLayout()
        main_layout.addWidget(self.table)
        main_layout.addLayout(btn_layout)
        self.setLayout(main_layout)

    def refresh_table(self):
        self.table.setRowCount(0)
        for name, seq_obj in self.sequences_dict.items():
            row = self.table.rowCount()
            self.table.insertRow(row)

            if isinstance(seq_obj, sequences.MutableArraySequence) or isinstance(seq_obj, sequences.ImmutableArraySequence):
                struct_type = "ARRAY"
            else:
                struct_type = "LIST"

            mutability = "MUTABLE" if "Mutable" in type(seq_obj).__name__ else "IMMUTABLE"
            length = seq_obj.getLength()

            content = " ".join(str(seq_obj.get(i)) for i in range(length))

            self.table.setItem(row, 0, QTableWidgetItem(name))
            self.table.setItem(row, 1, QTableWidgetItem(struct_type))
            self.table.setItem(row, 2, QTableWidgetItem("INT"))
            self.table.setItem(row, 3, QTableWidgetItem(mutability))
            self.table.setItem(row, 4, QTableWidgetItem(str(length)))
            self.table.setItem(row, 5, QTableWidgetItem(content))

    def create_sequence(self):
        dlg = CreateDialog(self)
        if dlg.exec_() == QDialog.Accepted:
            name, struct_type, data_type, mutability, elements = dlg.get_values()
            if not name:
                QMessageBox.warning(self, "ERROR", "Sequence must be named")
                return
            if name in self.sequences_dict:
                QMessageBox.warning(self, "ERROR", f"Sequence '{name}' already exists")
                return

            if struct_type == "ARRAY":
                if mutability == "MUTABLE":
                    seq_obj = sequences.MutableArraySequence(elements) if elements else sequences.MutableArraySequence()
                else:
                    seq_obj = sequences.ImmutableArraySequence(elements) if elements else sequences.ImmutableArraySequence()
            else:  
                if mutability == "MUTABLE":
                    seq_obj = sequences.MutableListSequence(elements) if elements else sequences.MutableListSequence()
                else:
                    seq_obj = sequences.ImmutableListSequence(elements) if elements else sequences.ImmutableListSequence()

            self.sequences_dict[name] = seq_obj
            self.refresh_table()

    def get_selected_sequence(self):
        selected = self.table.currentRow()
        if selected < 0:
            QMessageBox.warning(self, "ERROR", "First choose the sequence")
            return None, None
        name = self.table.item(selected, 0).text()
        return name, self.sequences_dict[name]

    def is_immutable(self, seq):
        
        return (
            isinstance(seq, sequences.ImmutableArraySequence)
            or isinstance(seq, sequences.ImmutableListSequence)
        )

    def select_sequence(self):
        name, seq = self.get_selected_sequence()
        if seq is not None:
            QMessageBox.information(self, "Selected", f"Selected Sequence: {name}")

    def delete_sequence(self):
        name, seq = self.get_selected_sequence()
        if seq is not None:
            del self.sequences_dict[name]
            self.refresh_table()

    def append_value(self):
        name, seq = self.get_selected_sequence()
        if seq is None:
            return
        value, ok = QInputDialog.getInt(self, "Append", "Enter an INT number:")
        if not ok:
            return
        try:
            if self.is_immutable(seq):
                new_seq = seq.append(value)
                new_name = name + "(copy)"
                counter = 1
                base_name = new_name
                while new_name in self.sequences_dict:
                    new_name = f"{base_name}_{counter}"
                    counter += 1
                self.sequences_dict[new_name] = new_seq
            else:
                seq.append(value)
            self.refresh_table()
        except Exception as e:
            QMessageBox.warning(self, "ERROR", str(e))

    def prepend_value(self):
        name, seq = self.get_selected_sequence()
        if seq is None:
            return
        value, ok = QInputDialog.getInt(self, "Prepend", "Enter an INT number:")
        if not ok:
            return
        try:
            if self.is_immutable(seq):
                new_seq = seq.prepend(value)
                new_name = name + "(copy)"
                counter = 1
                base_name = new_name
                while new_name in self.sequences_dict:
                    new_name = f"{base_name}_{counter}"
                    counter += 1
                self.sequences_dict[new_name] = new_seq
            else:
                seq.prepend(value)
            self.refresh_table()
        except Exception as e:
            QMessageBox.warning(self, "ERROR", str(e))

    def insert_value(self):
        name, seq = self.get_selected_sequence()
        if seq is None:
            return
        idx, ok1 = QInputDialog.getInt(self, "InsertAt", "Enter an Index:")
        if not ok1:
            return
        value, ok2 = QInputDialog.getInt(self, "InsertAt", "Enter an INT number:")
        if not ok2:
            return
        try:
            if self.is_immutable(seq):
                new_seq = seq.insertAt(value, idx)
                new_name = name + "(copy)"
                counter = 1
                base_name = new_name
                while new_name in self.sequences_dict:
                    new_name = f"{base_name}_{counter}"
                    counter += 1
                self.sequences_dict[new_name] = new_seq
            else:
                seq.insertAt(value, idx)
            self.refresh_table()
        except Exception as e:
            QMessageBox.warning(self, "ERROR", str(e))

    def concat_sequence(self):
        name, seq = self.get_selected_sequence()
        if seq is None:
            return
        other_name, ok = QInputDialog.getText(self, "Concat", "Enter name for concatination:")
        if not ok or not other_name:
            return
        if other_name not in self.sequences_dict:
            QMessageBox.warning(self, "ERROR", f"Sequence '{other_name}' does`t exsist.")
            return

        other_seq = self.sequences_dict[other_name]
        try:
            new_seq = seq.concat(other_seq)
            if self.is_immutable(seq):
                base_name = f"{name} (concat {other_name})"
                new_name = base_name
                counter = 1
                while new_name in self.sequences_dict:
                    new_name = f"{base_name}_{counter}"
                    counter += 1
                self.sequences_dict[new_name] = new_seq
            else:
                self.sequences_dict[name] = new_seq
            self.refresh_table()
        except Exception as e:
            QMessageBox.warning(self, "Error", str(e))
