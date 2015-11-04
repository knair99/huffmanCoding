#ifndef HUFFMAN_CC 
#define HUFFMAN_CC 

#include "huff.h"

using std::string;          using std::ios;         using std::cout; 
using std::fstream;         using std::map;         using std::endl;
using std::priority_queue;  using std::noskipws;    using std::getline;

//HuffCode::Encode
//Call overloaded Encode with filestream, 
//after opening stream
long HuffCode::Encode(const string& in_file_name, const string& out_file_name) const
{
    long ret = FAILURE;
 
    fstream in_file, out_file;
    in_file.open(in_file_name, fstream::in);
    out_file.open(out_file_name, fstream::out);

    Encode(in_file, out_file);
    return ret;
}

//HuffCode::Decode
//Call overloaded Decode with filestream, 
//after opening stream
long HuffCode::Decode(const string& in_file_name, const string& out_file_name) const
{
    long ret = FAILURE;
    
    fstream in_file, out_file;
    in_file.open(in_file_name, fstream::in);
    out_file.open(out_file_name, fstream::out);
    
    Decode(in_file, out_file);
    return ret;
}


//HuffCode::Encode
//Encode input file from stream
//Save as output file from stream
//Save the huffcodes in ouput file
//OUTPUT FILE: [HUFFCODES][SENTINAL][BITSTREAM]
long HuffCode::Encode(fstream& in_file, fstream& out_file) const
{
    long ret = FAILURE;
    PriorityQueue q_nodes;
    CountMap      map_count;
    EncodeMap     map_encode;
    Node*         root_node;

    //Build count map
    BuildCountMap (in_file, map_count);

    //Build priority queue in min heap manner of character nodes
    for(CountMap::const_iterator map_itr = map_count.begin(); map_itr != map_count.end(); ++map_itr)
    {
        q_nodes.push(new Node(NULL, NULL, true, map_itr->first, map_itr->second));
    }
    
    //Build Huffman tree with priority queue
    BuildHuffTree(root_node, q_nodes);
    
    //Build Huffman code table with tree
    string s_encode;
    BuildHuffTable(root_node, s_encode, map_encode); 

    //Save huffmap first to output file
    for(EncodeMap::const_iterator map_itr = map_encode.begin(); map_itr != map_encode.end(); ++map_itr)
    {
        out_file << map_itr->first << " " << map_itr->second << " " << endl;
    }

    //Write a sentinel character to after this
    out_file << "$" << endl;

    //Encode the input file into output
    in_file.clear();
    in_file.seekg(0, ios::beg); char ch = char();
    while(in_file >> noskipws >> ch)
    {
        out_file << map_encode[ch] << " ";
    }

    //Clean up and finish
    CleanUp(root_node);
    in_file.close();
    out_file.close();
    return ret;
}


//HuffCode::Decode
//Decode input file
//Save as output file
long HuffCode::Decode(fstream& in_file, fstream& out_file) const
{
    long ret = FAILURE;
    char ch = char();
    string s;
    DecodeMap map_decode;

    //First build the decode map
    while(getline(in_file, s) && !s.compare("$"))
    {
        
    }

    return ret;
}

//HuffCode::BuildCountMap
//Builds map of characters
//And their counts in input
long HuffCode::BuildCountMap(fstream& in_file, CountMap& map_count) const
{
    long ret = FAILURE;
    char ch  = char();
    
    while (in_file >> noskipws >> ch)
    {
        map_count[ch]++; 
    }
    return ret;
}

//HuffCode::BuildHuffTree
//Builds huffman tree from 
//priority queue
long HuffCode::BuildHuffTree(Node*& node, PriorityQueue& q_nodes) const
{
    long ret = FAILURE;
    while(q_nodes.size() > 1)
    {
        //Get the two smallest nodes
        Node* left  = q_nodes.top(); q_nodes.pop();
        Node* right = q_nodes.top(); q_nodes.pop();
        
        //Create new node with above, mark it as not leaf, add back to q 
        q_nodes.push(new Node(left, right, false, '!', left->weight + right->weight));

        //Check for root (last node in q) & assign
        if(q_nodes.size() == 1) node = q_nodes.top();
    } 
    return ret;
}


//HuffCode::BuildHuffTable
//Builds huffman code table 
//from huffman tree 
//Visits all nodes in post order recursion
long HuffCode::BuildHuffTable(Node*& node, string hcode, EncodeMap& map_encode) const
{
    long ret = FAILURE;
    if(node->is_leaf == true)
    {
        map_encode[node->data] = hcode;
        return SUCCESS;
    }
    
    hcode += "0";
    BuildHuffTable(node->left, hcode, map_encode);

    hcode += "1";
    BuildHuffTable(node->right, hcode, map_encode);
    
    return ret;
}


//Clean up all allocated memory 
//TODO : Replace with automatic ptr
//Follows post order deletion algorithm
void HuffCode::CleanUp(Node*& node) const
{
    if(node == NULL)    return;

    CleanUp(node->left);
    CleanUp(node->right);
    delete node;
}


#endif //HUFFMAN_CC 
