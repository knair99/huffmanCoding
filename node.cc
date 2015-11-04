#include "node.h"

Node::Node(Node* _left, Node* _right, bool _is_leaf, char _data, int _weight): 
            left(_left), right(_right), is_leaf(_is_leaf), 
            data(_data), weight(_weight)
{
    //Construct other node related stuff here
}  
