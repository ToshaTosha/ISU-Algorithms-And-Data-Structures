from enum import Enum
import struct


class Alignment(Enum):
    HORIZONTAL = 1
    VERTICAL = 2


class Widget():
    def __init__(self, parent):
        self.parent = parent
        self.childrens = []
        if self.parent is not None:
            self.parent.add_children(self)

    def add_children(self, children: "Widget"):
        self.childrens.append(children)

    def to_binary(self):
        classname_bytes = self.__class__.__name__.encode()
        result = struct.pack("i", len(classname_bytes)) + classname_bytes

        if classname_bytes == b'Layout':
            alignment_bytes = struct.pack("i", self.alignment.value)
            result += alignment_bytes
        elif classname_bytes == b"LineEdit":
            max_length_bytes = struct.pack("i", self.max_length)
            result += max_length_bytes
        elif classname_bytes == b"ComboBox":
            items_bytes = ';'.join(str(item) for item in self.items).encode()
            items_length_bytes = struct.pack("i", len(items_bytes))
            result += items_length_bytes + items_bytes
        elif classname_bytes == b"MainWindow":
            title_bytes = self.title.encode()
            title_length_bytes = struct.pack("i", len(title_bytes))
            result += title_length_bytes + title_bytes

        children_data = b"".join(child.to_binary() for child in self.childrens)
        children_data_length_bytes = struct.pack("i", len(children_data))
        result += children_data_length_bytes + children_data

        return result

    @classmethod
    def from_binary(cls, binary_data, parent=None):
        class_len = struct.unpack("i", binary_data[:4])[0]
        current = 4
        class_name = binary_data[current:current + class_len].decode()
        current += class_len

        prop_len = struct.unpack("i", binary_data[current:current + 4])[0]
        current += 4
        prop_val = binary_data[current:current + prop_len].decode()
        current += prop_len

        root = None
        if class_name == "MainWindow":
            root = cls(prop_val)
        elif class_name == "Layout":
            current -= prop_len
            root = Layout(parent, prop_len)
        elif class_name == "LineEdit":
            current -= prop_len
            root = LineEdit(parent, prop_len)
        elif class_name == "ComboBox":
            root = ComboBox(parent, prop_val)

        child_len = struct.unpack("i", binary_data[current:current + 4])[0]
        current += 4
        child_data = binary_data[current:]

        cursor = 0
        while cursor < child_len:
            child, cur_cursor = root.from_binary(child_data[cursor:], parent=root)
            cursor += cur_cursor

        return root, current + cursor


    def __str__(self):
        return f"{self.__class__.__name__}{self.childrens}"

    def __repr__(self):
        return str(self)


class MainWindow(Widget):
    def __init__(self, title: str):
        super().__init__(None)
        self.title = title


class Layout(Widget):
    def __init__(self, parent, alignment: Alignment):
        super().__init__(parent)
        self.alignment = alignment


class LineEdit(Widget):
    def __init__(self, parent, max_length: int=10):
        super().__init__(parent)
        self.max_length = max_length


class ComboBox(Widget):
    def __init__(self, parent, items):
        super().__init__(parent)
        self.items = items


app = MainWindow("Application")
layout1 = Layout(app, Alignment.HORIZONTAL)
layout2 = Layout(app, Alignment.VERTICAL)

edit1 = LineEdit(layout1, 20)
edit2 = LineEdit(layout1, 30)

box1 = ComboBox(layout2, [1, 2, 3, 4])
box2 = ComboBox(layout2, ["a", "b", "c"])

print(app)

bts = app.to_binary()
print(f"Binary data length {len(bts)}")

new_app = MainWindow.from_binary(bts)
print(new_app)