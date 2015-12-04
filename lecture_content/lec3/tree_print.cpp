#include <iostream>
#include <string>
#include <map>
using namespace std;

class FileRecord {
public:
    map<string, FileRecord> members;
    void add(string s) {
        string::size_type offset = s.find_first_of("/\\");
        string base = s.substr(0, offset);
        members[base];
        if(base != s) {
            members[base].add(s.substr(offset + 1));
        }
    }

    void printMembers(int indent) {
        for (auto it = members.begin(); it != members.end(); it++) {
            cout << string(indent, ' ') << it->first << endl;
            it->second.printMembers(indent + 4);
        }
    }
};
int main(int argc, char **argv)
{
    FileRecord root;
    for(char **argscanner = argv + 1; argscanner < argv + argc; argscanner++) {
        root.add(*argscanner);
    }
    root.printMembers(0);
}
