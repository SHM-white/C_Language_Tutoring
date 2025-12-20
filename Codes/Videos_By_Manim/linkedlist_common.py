from manim import *
import numpy as np


class NodeBox(VGroup):
    def __init__(self, value: int, **kwargs):
        super().__init__(**kwargs)
        data_box = Rectangle(width=1.35, height=0.38, color=WHITE)
        next_box = Rectangle(width=1.35, height=0.30, color=WHITE)
        next_box.next_to(data_box, DOWN, buff=0)
        val_txt = Text(str(value), font="Consolas", weight=BOLD).scale(0.46)
        val_txt.move_to(data_box.get_center())
        self.data_box = data_box
        self.next_box = next_box
        self.add(data_box, next_box, val_txt)

    def set_value(self, value: int):
        self[2].set_text(str(value))


def make_pointer(label: str, target: Mobject, direction=UP, buff=0.3):
    tag = Text(label, font="Consolas").scale(0.55)
    tag.next_to(target, direction, buff=buff)
    if direction is DOWN:
        pointer = Arrow(tag.get_top(), target.get_bottom(), buff=0.08, stroke_width=4)
    else:
        pointer = Arrow(tag.get_bottom(), target.get_top(), buff=0.08, stroke_width=4)
    return VGroup(tag, pointer)


def surround_line_rect(code: Code, line_no: int, color=YELLOW):
    try:
        line_mobj = code.code[line_no - 1]
    except Exception:
        line_mobj = code.submobjects[-1][line_no - 1]
    rect = SurroundingRectangle(line_mobj, color=color, buff=0.05)
    rect.set_stroke(color, width=3)
    rect.set_fill(color, opacity=0.12)
    return rect


def node_arrow(left_node: NodeBox, right_node: NodeBox):
    return Arrow(left_node.next_box.get_right(), right_node.data_box.get_left(), buff=0.12, stroke_width=3)
