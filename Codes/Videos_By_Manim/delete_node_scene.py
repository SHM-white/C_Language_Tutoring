from manim import *
import numpy as np
from linkedlist_common import NodeBox, make_pointer, surround_line_rect, node_arrow

DELETE_NODE_CODE = r"""// Delete a node from the linked list
void deleteNode(Node** head_ref, int key) {
    Node* current = *head_ref;
    Node* prev = NULL;
    while(current!= NULL && current->data!= key) {
        prev = current;
        current = current->next;
    }
    if(current == NULL) return;
    if(prev == NULL) {
        *head_ref = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
}
"""


class DeleteNodeScene(Scene):
    def construct(self):
        title = Text("链表删除 (deleteNode)", font="Microsoft YaHei").scale(0.6)
        title.to_edge(UP)
        self.add(title)

        code = Code(
            code_string=DELETE_NODE_CODE,
            language="c",
            background="window",
            formatter_style="monokai",
            add_line_numbers=True,
        )
        code.set(width=config.frame_width * 0.4)
        code.scale(0.72)
        code.to_edge(RIGHT, buff=0.3)
        code.line_spacing = 0.8
        self.add(code)

        hl = surround_line_rect(code, 1)
        self.add(hl)

        values = [2, 4, 6, 8]
        target = 6
        nodes = VGroup(*[NodeBox(v) for v in values])
        for i, n in enumerate(nodes):
            n.move_to(np.array([-5.4 + 2.6 * i, -0.4, 0]))
        self.play(LaggedStart(*[FadeIn(n) for n in nodes], lag_ratio=0.1))

        arrows = VGroup()
        for i in range(len(nodes) - 1):
            arrows.add(node_arrow(nodes[i], nodes[i + 1]))
        self.play(LaggedStart(*[Create(a) for a in arrows], lag_ratio=0.1))

        head_ptr = make_pointer("head", nodes[0])
        curr_ptr = make_pointer("current", nodes[0])
        prev_ptr = make_pointer("prev", nodes[0], direction=DOWN)
        self.play(FadeIn(head_ptr), FadeIn(curr_ptr), FadeIn(prev_ptr))
        prev_ptr.set_opacity(0)

        # signature
        hl_target = surround_line_rect(code, 2)
        self.play(ReplacementTransform(hl, hl_target), run_time=0.45)
        hl = hl_target

        # init current, prev
        for line_no in (3, 4):
            hl_target = surround_line_rect(code, line_no)
            self.play(ReplacementTransform(hl, hl_target), run_time=0.35)
            hl = hl_target

        # while loop traverse until data == key (6)
        hl_target = surround_line_rect(code, 5)
        self.play(ReplacementTransform(hl, hl_target), run_time=0.35)
        hl = hl_target

        # step 1: move prev to 2, current to 4
        self.play(prev_ptr.animate.set_opacity(1), run_time=0.2)
        self.play(
            prev_ptr.animate.become(make_pointer("prev", nodes[0], direction=DOWN)),
            curr_ptr.animate.become(make_pointer("current", nodes[1])),
        )
        # loop check again
        self.play(ReplacementTransform(hl, surround_line_rect(code, 5)), run_time=0.3)
        hl = surround_line_rect(code, 5)

        # step 2: move prev to 4, current to 6 (target)
        self.play(
            prev_ptr.animate.become(make_pointer("prev", nodes[1], direction=DOWN)),
            curr_ptr.animate.become(make_pointer("current", nodes[2])),
        )

        # if current NULL? no
        hl_target = surround_line_rect(code, 7)
        self.play(ReplacementTransform(hl, hl_target), run_time=0.3)
        hl = hl_target

        # prev not NULL branch
        hl_target = surround_line_rect(code, 10)
        self.play(ReplacementTransform(hl, hl_target), run_time=0.35)
        hl = hl_target
        # reconnect prev->next to current->next (skip target)
        new_arrow = node_arrow(nodes[1], nodes[3])
        self.play(FadeOut(arrows[1]), FadeOut(arrows[2]), Create(new_arrow))
        arrows[1] = new_arrow

        # free current (fade out target node and pointer)
        hl_target = surround_line_rect(code, 12)
        self.play(ReplacementTransform(hl, hl_target), run_time=0.35)
        hl = hl_target
        self.play(FadeOut(nodes[2]), FadeOut(curr_ptr))

        self.wait(0.8)


if __name__ == "__main__":
    config.quality = "low_quality"
    scene = DeleteNodeScene()
    scene.render()
