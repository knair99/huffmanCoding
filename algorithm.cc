#include <iostream>
#include <map>
#include <queue>
#include <string>

using std::map;         using std::priority_queue;      using std::less; 
using std::cout;        using std::cin;                 using std::vector;
using std::endl;        using std::string;                     

typedef std::map<char, int> map_;
typedef std::map<char, string> map_c;
typedef std::map<string, char> map_d;

//Node of a huffman tree
class Node
{
    public:
        Node    *left, *right;
        int     weight; 
                char    data; 
                bool    is_leaf;

        Node() : left(NULL), right(NULL), weight(0), is_leaf(true) {}

        Node(Node* _left, Node* _right, bool _is_leaf, char _data, int _weight): 
        left(_left), right(_right), is_leaf(_is_leaf), data(_data), weight(_weight)
        {
        }  

        ~Node() {left = right = NULL;}
};

//Queues in std library needs a comparator class
struct NodeComparator
{
        bool operator() (const Node* lhs, const Node* rhs) const { return lhs->weight > rhs->weight;}
};
typedef std::priority_queue<Node*, vector<Node*>, NodeComparator> queue_;

//build map out of input string
void build_count_map(const string& s_in, map_& map_count)
{
    for( string::const_iterator s_itr = s_in.begin(); s_itr != s_in.end(); ++s_itr)
    {
        map_count[*s_itr]++;    
    }
}

//Build huffman tree
void build_huffman_tree(Node*& root_node, queue_& q_nodes)
{
    while(q_nodes.size() > 1)
    {
        //Get the two smallest nodes
        Node* left      = q_nodes.top(); q_nodes.pop();
        Node* right = q_nodes.top(); q_nodes.pop();
        
        //Create new node with above, mark it as not leaf, add back to q 
        q_nodes.push(new Node(left, right, false, '!', left->weight + right->weight));

        //Check for root (last node in q) & assign
        if(q_nodes.size() == 1) root_node = q_nodes.top();
    } 
}

//Post order deletion of tree
void post_order_delete(Node*& node)
{
    if(node == NULL) return;
    post_order_delete(node->left);
    post_order_delete(node->right);
    delete(node);
}

//Build map from huffman tree
void post_order_build_codes(Node*& node, string hcode, map_c& map_encoder)
{    
    if(node->is_leaf == true)
    {
        map_encoder[node->data] = hcode;
        return;
    }
    hcode += "0";
    post_order_build_codes(node->left, hcode, map_encoder);
    hcode += "1";
    post_order_build_codes(node->right, hcode, map_encoder);
}

//Encode input string 
void encode_string (const string& s_in, string& s_out, map_c& map_encoder)
{
    for( string::const_iterator s_itr = s_in.begin(); s_itr != s_in.end(); ++s_itr)
    {
        s_out += map_encoder[*s_itr];
        s_out += " ";
    }
}

//Decode string back
void decode_string (const string& s_in, string& s_out, map_d& map_decoder)
{
    string s_tmp;
    for( string::const_iterator s_itr = s_in.begin(); s_itr != s_in.end(); ++s_itr)
    {
        if(*s_itr == ' ')
        {
            s_out += map_decoder[s_tmp]; 
            s_tmp = "";
        }
        else
        {
            s_tmp += *s_itr;
        }
    }
}

//Main
int main(int argc, char *argv[])
{
    string s_in = "the quick brown fox jumps over the lazy dog";
   
    //1. First, build a map of character counts
    map_    map_count;
    build_count_map(s_in, map_count);

    //2. Next build nodes for each character and throw them into the Q
    queue_  q_nodes;
    for(map_::const_iterator map_itr = map_count.begin(); map_itr != map_count.end(); ++map_itr)
    {
        //Insert node with null left & right child, leaf = true, with data and weight from map
        q_nodes.push(new Node(NULL, NULL, true, map_itr->first, map_itr->second));
    }

    //3. Build the huffman tree
    Node* root_node;
    build_huffman_tree(root_node, q_nodes);

    //4. Visit the tree in postorder and build an huffman coded map
    map_c   map_encoder; 
    string  hcode;
    post_order_build_codes(root_node, hcode, map_encoder);

    //Test and build decoder map
    map_d   map_decoder;
    for(map_c::const_iterator map_itr = map_encoder.begin(); map_itr != map_encoder.end(); ++map_itr)
    {  
        map_decoder[map_itr->second] = map_itr->first;
    }

    //5. Encode string
    string s_encoded;
    encode_string(s_in, s_encoded, map_encoder);
    cout << "Encoded string is: " << s_encoded << endl;

    //6. Decode string
    string s_decoded;
    decode_string(s_encoded, s_decoded, map_decoder);
    cout << "Decoded string is: " << s_in << endl;

    //7. Clean up
    post_order_delete(root_node);
    
    return 0;    
}
