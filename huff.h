#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "error_codes.h"
#include "node.h"
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <iosfwd>
#include <fstream>

typedef std::map<char, int>     CountMap;
typedef std::map<char, std::string>  EncodeMap;
typedef std::map<std::string, char>  DecodeMap;
typedef std::priority_queue<Node*, std::vector<Node*>, NodeComparator> PriorityQueue;


//The base class for all things Huff
//Abstract base class
class HuffCode
{
    public:
        HuffCode(){}
        virtual ~HuffCode() {};

        //Define methods
        long Encode(std::fstream& s_in, std::fstream& s_out) const;
        long Decode(std::fstream& s_in, std::fstream& s_out) const;
        long Encode(const std::string& in_file, const std::string& out_file) const;
        long Decode(const std::string& in_file, const std::string& out_file) const;

    private:
        long BuildCountMap(std::fstream&, CountMap&) const;       
        long BuildHuffTree(Node*&, PriorityQueue&) const;       
        long BuildHuffTable(Node*&, std::string, EncodeMap&) const;      
        void CleanUp(Node*&) const;
 };

#endif //HUFFMAN_H 
