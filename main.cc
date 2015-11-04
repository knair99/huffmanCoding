#include <iostream>
#include <map>
#include <queue>
#include "huff.h"


using std::map;         using std::priority_queue;
using std::cout;        using std::cin;
using std::endl;        using std::string;

int main(int argc, char *argv[])
{

    HuffCode hc;

    hc.Encode("kk.txt", "out.txt");

    hc.Decode("out.txt", "new.txt");

    return 0;    
}

