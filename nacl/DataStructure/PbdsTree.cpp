#include <bits/extc++.h>
using namespace __gnu_pbds;
using BST = tree<int, null_type, less<int>, splay_tree_tag,
                 tree_order_statistics_node_update>;
// rb_tree_tag with log^2(n) split
using BST_Itr = BST::iterator;
BST tr;
// overload std::distance for BST for efficiently split
namespace std {
template <>
iterator_traits<BST_Itr>::difference_type
distance(BST_Itr begin, BST_Itr end) {
    if(begin == end) return 0;
    auto it = begin.m_p_nd;
    // jump until root
    while(it->m_p_parent->m_p_parent != it) it = it->m_p_parent;
    // returns the size for the whole tree (only for split)
    return it->get_metadata();
}
} // namespace std
void splayAfterSplit(BST &bst) {
    if(bst.empty()) return;
    bst.find(*bst.begin());
}
/*
除了 tr.lower_bound(x) upper_bound insert same as rope<int>
tr.find_by_order(k); //return kth iterator; k=[0,tr.size())
                     //out of this will get tr.end()
tr.order_of_key(val); //return rank(val);
tr.join(tr2); //merge tr
and tr2, tr2.clear() tr.split(const int&r,RBTree&tr2); //<r
will in tr, >=r will in tr2
*/