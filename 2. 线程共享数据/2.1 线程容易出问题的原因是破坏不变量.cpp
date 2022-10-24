// 双向链表 A ↔ B ↔ C
// 不变量: 若 A -> B, 则 B -> A
void delete_node(Node B)
{
    n->pre->next = n->next;     // A -> C
                                // 此时A B C 之间的不变量被破坏, 其余线程访问 A B C 时就出问题了
    n->next->pre = n->pre;      // C -> A
    delete n;
}
