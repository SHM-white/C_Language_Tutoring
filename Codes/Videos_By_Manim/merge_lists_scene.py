from manim import *
import numpy as np
from linkedlist_common import NodeBox, make_pointer, surround_line_rect, node_arrow

MERGE_LISTS_CODE = r"""// Merge two linked lists
Node* mergeLists(Node* a, Node* b) {
    Node* result = NULL;
    Node** tail = &result;
    while(a!= NULL && b!= NULL) {
        if(a->data < b->data) {
            *tail = a;
            a = a->next;
        } else {
            *tail = b;
            b = b->next;
        }
        tail = &((*tail)->next);
    }
    if(a!= NULL) {
        *tail = a;
    } else {
        *tail = b;
    }
    return result;
}
"""


class MergeListsScene(Scene):
    def construct(self):
        title = Text("链表合并 (mergeLists)", font="Microsoft YaHei").scale(0.6)
        title.to_edge(UP)
        self.add(title)

        code = Code(
            code_string=MERGE_LISTS_CODE,
            language="c",
            background="window",
            formatter_style="monokai",
            add_line_numbers=True,
        )
        code.set(width=config.frame_width * 0.42)
        code.scale(0.72)
        code.to_edge(RIGHT, buff=0.25)
        code.line_spacing = 0.8
        self.add(code)

        hl = surround_line_rect(code, 1)
        self.add(hl)

        a_vals = [1, 4, 8]
        b_vals = [2, 3, 9]
        a_nodes = VGroup(*[NodeBox(v) for v in a_vals])
        b_nodes = VGroup(*[NodeBox(v) for v in b_vals])
        for i, n in enumerate(a_nodes):
            n.move_to(np.array([-5.6 + 2.6 * i, 1.0, 0]))
        for i, n in enumerate(b_nodes):
            n.move_to(np.array([-5.6 + 2.6 * i, -1.6, 0]))
        self.play(LaggedStart(*[FadeIn(n) for n in a_nodes], lag_ratio=0.1))
        self.play(LaggedStart(*[FadeIn(n) for n in b_nodes], lag_ratio=0.1))

        a_arrows = VGroup(*[node_arrow(a_nodes[i], a_nodes[i + 1]) for i in range(len(a_nodes) - 1)])
        b_arrows = VGroup(*[node_arrow(b_nodes[i], b_nodes[i + 1]) for i in range(len(b_nodes) - 1)])
        self.play(LaggedStart(*[Create(a) for a in a_arrows], lag_ratio=0.1))
        self.play(LaggedStart(*[Create(a) for a in b_arrows], lag_ratio=0.1))

        head_a = make_pointer("a", a_nodes[0])
        head_b = make_pointer("b", b_nodes[0])
        tail_ptr = make_pointer("tail", a_nodes[0], direction=DOWN)
        result_ptr = make_pointer("result", a_nodes[0], direction=DOWN)
        self.play(FadeIn(head_a), FadeIn(head_b), FadeIn(tail_ptr), FadeIn(result_ptr))
        result_ptr.set_opacity(0)
        tail_ptr.set_opacity(0)

        result_nodes = []
        tail_target = None

        # signature
        hl_target = surround_line_rect(code, 2)
        self.play(ReplacementTransform(hl, hl_target), run_time=0.45)
        hl = hl_target

        # init result, tail
        for line_no in (3, 4):
            hl_target = surround_line_rect(code, line_no)
            self.play(ReplacementTransform(hl, hl_target), run_time=0.35)
            hl = hl_target

        # while loop iterations (simulate merge)
        pairs = [(a_nodes[0], 'a'), (b_nodes[0], 'b'), (b_nodes[1], 'b'), (a_nodes[1], 'a'), (a_nodes[2], 'a'), (b_nodes[2], 'b')]
        current_tail_arrow = None

        for node, src in pairs:
            # while condition
            hl_target = surround_line_rect(code, 5)
            self.play(ReplacementTransform(hl, hl_target), run_time=0.35)
            hl = hl_target

            # compare branch
            branch_line = 6 if src == 'a' else 7
            hl_target = surround_line_rect(code, branch_line)
            self.play(ReplacementTransform(hl, hl_target), run_time=0.35)
            hl = hl_target

            # attach node to result
            hl_target = surround_line_rect(code, 8)
            self.play(ReplacementTransform(hl, hl_target), run_time=0.3)
            hl = hl_target
            if not result_nodes:
                result_ptr.set_opacity(1)
                tail_ptr.set_opacity(1)
                result_ptr.become(make_pointer("result", node, direction=DOWN))
                tail_ptr.become(make_pointer("tail", node, direction=DOWN))
            else:
                # link from tail to node
                link = node_arrow(tail_target, node)
                self.play(Create(link))
            result_nodes.append(node)
            tail_target = node

            # advance chosen list pointer
            advance_line = 7 if src == 'a' else 8
            hl_target = surround_line_rect(code, advance_line)
            self.play(ReplacementTransform(hl, hl_target), run_time=0.3)
            hl = hl_target
            if src == 'a':
                if len(a_nodes) > 1:
                    head_a = make_pointer("a", a_nodes[min(len(result_nodes), len(a_nodes)-1)])
            else:
                if len(b_nodes) > 1:
                    head_b = make_pointer("b", b_nodes[min(len(result_nodes), len(b_nodes)-1)])
            tail_ptr.become(make_pointer("tail", tail_target, direction=DOWN))

            # move while tail pointer
            hl_target = surround_line_rect(code, 10)
            self.play(ReplacementTransform(hl, hl_target), run_time=0.3)
            hl = hl_target

        # handle remainder (else part)
        hl_target = surround_line_rect(code, 11)
        self.play(ReplacementTransform(hl, hl_target), run_time=0.35)
        hl = hl_target

        hl_target = surround_line_rect(code, 12)
        self.play(ReplacementTransform(hl, hl_target), run_time=0.35)
        hl = hl_target

        hl_target = surround_line_rect(code, 14)
        self.play(ReplacementTransform(hl, hl_target), run_time=0.35)
        hl = hl_target

        self.wait(1)


if __name__ == "__main__":
    config.quality = "low_quality"
    scene = MergeListsScene()
    scene.render()
