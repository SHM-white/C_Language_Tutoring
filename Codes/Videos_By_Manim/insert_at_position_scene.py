from manim import *
import numpy as np
from linkedlist_common import NodeBox, make_pointer, surround_line_rect, node_arrow

INSERT_AT_POSITION_CODE = r"""// Insert a new node at the target position of the linked list
void insertAtPosition(Node** head_ref, int new_data, int position) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = new_data;
    Node* current = *head_ref;
    Node* prev = NULL;
    int i = 1;
    while(current!= NULL && i < position) {
        prev = current;
        current = current->next;
        i++;
    }
    if(current == NULL) {
        printf("Position is out of range.\n");
        return;
    }
    new_node->next = current;
    if(prev == NULL) {
        *head_ref = new_node;
    } else {
        prev->next = new_node;
    }
}
"""


class InsertAtPositionScene(Scene):
    def construct(self):
        title = Text("链表插入 (insertAtPosition)", font="Microsoft YaHei").scale(0.6)
        title.to_edge(UP)
        self.add(title)

        code = Code(
            code_string=INSERT_AT_POSITION_CODE,
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

        values = [3, 5, 7]
        nodes = VGroup(*[NodeBox(v) for v in values])
        for i, n in enumerate(nodes):
            n.move_to(np.array([-5.4 + 2.8 * i, -0.4, 0]))
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

        insert_value = 9
        position = 2

        hl_target = surround_line_rect(code, 2)
        self.play(ReplacementTransform(hl, hl_target), run_time=0.5)
        hl = hl_target

        for line_no in (3, 4):
            hl_target = surround_line_rect(code, line_no)
            self.play(ReplacementTransform(hl, hl_target), run_time=0.4)
            hl = hl_target
        new_node = NodeBox(insert_value)
        new_node.move_to(np.array([-5.4, -2.0, 0]))
        self.play(FadeIn(new_node))

        for line_no in (5, 6, 7):
            hl_target = surround_line_rect(code, line_no)
            self.play(ReplacementTransform(hl, hl_target), run_time=0.35)
            hl = hl_target

        hl_target = surround_line_rect(code, 8)
        self.play(ReplacementTransform(hl, hl_target), run_time=0.35)
        hl = hl_target

        self.play(prev_ptr.animate.set_opacity(1), run_time=0.2)
        self.play(
            prev_ptr.animate.become(make_pointer("prev", nodes[0], direction=DOWN)),
            curr_ptr.animate.become(make_pointer("current", nodes[1])),
        )

        hl_target = surround_line_rect(code, 13)
        self.play(ReplacementTransform(hl, hl_target), run_time=0.3)
        hl = hl_target

        hl_target = surround_line_rect(code, 16)
        self.play(ReplacementTransform(hl, hl_target), run_time=0.35)
        hl = hl_target
        link_new_to_cur = node_arrow(new_node, nodes[1])
        self.play(Create(link_new_to_cur))

        hl_target = surround_line_rect(code, 18)
        self.play(ReplacementTransform(hl, hl_target), run_time=0.35)
        hl = hl_target
        old_arrow = arrows[0]
        new_arrow = node_arrow(nodes[0], new_node)
        self.play(FadeOut(old_arrow), Create(new_arrow))
        arrows[0] = new_arrow
        arrows.add(link_new_to_cur)

        curr_ptr_new = make_pointer("current", new_node)
        self.play(curr_ptr.animate.become(curr_ptr_new))

        self.wait(0.8)


if __name__ == "__main__":
    config.quality = "low_quality"
    scene = InsertAtPositionScene()
    scene.render()
