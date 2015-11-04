#ifndef NODE_HH
#define NODE_HH

#include <iostream>

//Node of a huffman tree
class Node
{
    public:
        Node    *left, *right;
        int     weight; 
        char    data; 
        bool    is_leaf;

        Node() : left(NULL), right(NULL), weight(0), is_leaf(true) {}
        Node(Node* _left, Node* _right, bool _is_leaf, char _data, int _weight);
        ~Node() {left = right = NULL;}
};

//Queues in std library needs a comparator class
struct NodeComparator
{
        bool operator() (const Node* lhs, const Node* rhs) const 
        { 
            return lhs->weight > rhs->weight;
        }
};

#endif //NODE_HH

