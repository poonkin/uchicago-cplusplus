#include <iostream>
#include <boost/tokenizer.hpp>
#include <string>
#include <map>
using namespace std;
typedef boost::tokenizer<boost::char_separator<char> >  tokenizer;

class FileRecord {
public:
    map<string, FileRecord> members;
    void add(tokenizer::iterator beg, tokenizer::iterator end) {
        if(beg == end) return;
        string head = *beg++;
        members[head].add(beg, end);
    }
    void print(int indent) {
        for (map<string, FileRecord>::iterator it = members.begin();
             it != members.end(); it++) {
            cout << string(indent, ' ') << it->first << endl;
            it->second.print(indent + 4);
        }
    }
};
int main(int argc, char **argv)
{
    FileRecord root;
    boost::char_separator<char> sep("/\\");
    for(char **argscanner = argv + 1; argscanner < argv + argc; argscanner++) {
        string arg = *argscanner;
        tokenizer tokens(arg, sep);
        root.add(tokens.begin(), tokens.end());
    }
    root.print(0);
}
