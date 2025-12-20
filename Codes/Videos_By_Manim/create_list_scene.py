from manim import *
import numpy as np
from linkedlist_common import NodeBox, make_pointer, surround_line_rect, node_arrow

CREATE_NODE_CODE = r"""// Create a new node while inputting data in stdin
Node* createNode() {
    Node *head = NULL;
    Node *current = NULL;
    while(1){
        int input;
        printf("Enter data: ");
        scanf("%d", &input);
        if(input == -1) break;
        if(head == NULL) {
            head = (Node*)malloc(sizeof(Node));
            current = head;
        } else {
            current->next = (Node*)malloc(sizeof(Node));
            current = current->next;
        }
        current->data = input;
        current->next = NULL;
    } // 输入-1结束输入
    // 环形链表处理
    // current->next = head;
    return head;
}
"""


class CreateLinkedListScene(Scene):
    def construct(self):
        title = Text("链表创建 (createNode)", font="Microsoft YaHei").scale(0.6)
        title.to_edge(UP)
        self.add(title)

        code = Code(
            code_string=CREATE_NODE_CODE,
            language="c",
            background="window",
            formatter_style="monokai",
            add_line_numbers=True,
        )
        code.set(width=config.frame_width * 0.4)
        code.scale(1)
        code.to_edge(RIGHT, buff=0.3)
        code.line_spacing = 0.8
        self.add(code)

        hl = surround_line_rect(code, 1)
        self.add(hl)

        nodes = VGroup()
        arrows = VGroup()
        inputs = [3, 5, 7, -1]

        head_ptr = None
        curr_ptr = None

        hl_target = surround_line_rect(code, 2)
        self.play(ReplacementTransform(hl, hl_target), run_time=0.6)
        self.wait(0.2)
        hl = hl_target

        for line_no in (3, 4):
            hl_target = surround_line_rect(code, line_no)
            self.play(ReplacementTransform(hl, hl_target), run_time=0.5)
            hl = hl_target
        placeholder = Text("head = NULL\ncurrent = NULL", font="Consolas").scale(0.52)
        placeholder.to_edge(UL, buff=0.8).shift(LEFT * 0.5)
        self.play(FadeIn(placeholder))

        hl_target = surround_line_rect(code, 5)
        self.play(ReplacementTransform(hl, hl_target), run_time=0.5)
        hl = hl_target

        x_start = -5.4
        y_base = -0.4

        last_input_text = None

        for idx, val in enumerate(inputs):
            hl_target = surround_line_rect(code, 6)
            self.play(ReplacementTransform(hl, hl_target), run_time=0.4)
            hl = hl_target

            for line_no in (7, 8):
                hl_target = surround_line_rect(code, line_no)
                self.play(ReplacementTransform(hl, hl_target), run_time=0.35)
                hl = hl_target
            if last_input_text:
                self.play(FadeOut(last_input_text), run_time=0.2)
            input_text = Text(f"输入: {val}", font="Microsoft YaHei").scale(0.5)
            input_text.next_to(placeholder, DOWN, buff=0.2).align_to(placeholder, LEFT)
            self.play(FadeIn(input_text), run_time=0.3)
            last_input_text = input_text

            hl_target = surround_line_rect(code, 9)
            self.play(ReplacementTransform(hl, hl_target), run_time=0.3)
            hl = hl_target
            if val == -1:
                ret_hl = surround_line_rect(code, 22)
                self.play(ReplacementTransform(hl, ret_hl), run_time=0.5)
                self.wait(0.5)
                break

            hl_target = surround_line_rect(code, 10)
            self.play(ReplacementTransform(hl, hl_target), run_time=0.3)
            hl = hl_target

            node = NodeBox(val)
            node.move_to(np.array([x_start + 2.8 * idx, y_base, 0]))

            if len(nodes) == 0:
                for line_no in (11, 12):
                    hl_target = surround_line_rect(code, line_no)
                    self.play(ReplacementTransform(hl, hl_target), run_time=0.3)
                    hl = hl_target
                self.play(FadeIn(node), run_time=0.5)
                nodes.add(node)
                head_ptr = make_pointer("head", node)
                curr_ptr = make_pointer("current", node, direction=DOWN)
                placeholder_new = Text(f"head -> {val}\ncurrent -> {val}", font="Consolas").scale(0.5)
                placeholder_new.move_to(placeholder.get_center())
                self.play(FadeIn(head_ptr), FadeIn(curr_ptr), ReplacementTransform(placeholder, placeholder_new))
                placeholder = placeholder_new
            else:
                for line_no in (14, 15):
                    hl_target = surround_line_rect(code, line_no)
                    self.play(ReplacementTransform(hl, hl_target), run_time=0.3)
                    hl = hl_target
                self.play(FadeIn(node), run_time=0.5)
                nodes.add(node)
                prev = nodes[-2]
                start_point = prev.next_box.get_right()
                end_point = node.data_box.get_left()
                arrow = Arrow(start_point, end_point, buff=0.12, stroke_width=3)
                arrows.add(arrow)
                self.play(Create(arrow))
                curr_ptr_new = make_pointer("current", node, direction=DOWN)
                placeholder_new = Text(f"head -> {inputs[0]}\ncurrent -> {val}", font="Consolas").scale(0.5)
                placeholder_new.move_to(placeholder.get_center())
                self.play(curr_ptr.animate.become(curr_ptr_new), ReplacementTransform(placeholder, placeholder_new))
                placeholder = placeholder_new

            for line_no in (17, 18):
                hl_target = surround_line_rect(code, line_no)
                self.play(ReplacementTransform(hl, hl_target), run_time=0.3)
                hl = hl_target
            self.wait(0.1)

        end_comment_hl = surround_line_rect(code, 19, color=BLUE)
        self.play(ReplacementTransform(hl, end_comment_hl), run_time=0.4)
        hl = end_comment_hl
        self.wait(0.2)

        circ_hl = surround_line_rect(code, 21, color=GREEN)
        self.play(ReplacementTransform(hl, circ_hl), run_time=0.4)
        hl = circ_hl
        self.wait(0.2)

        ret_hl = surround_line_rect(code, 22)
        self.play(ReplacementTransform(hl, ret_hl), run_time=0.5)
        self.wait(0.8)


if __name__ == "__main__":
    config.quality = "low_quality"
    scene = CreateLinkedListScene()
    scene.render()
