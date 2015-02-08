#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <fstream>
#include <string>
#include <vector>

using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;

class Text{
public:
    Text() {}
    Text(string filePath) {
        string temp;
        std::ifstream file(filePath.c_str());
        while (!file.eof()) {
            std::getline(file, temp);
            lines.push_back(temp);
        }
        file.close();
    }
    void importFromFile(string filePath) {
        lines.clear();
        appendFromFile(filePath);
    }
    void appendFromFile(string filePath) {
        string temp;
        std::ifstream file(filePath.c_str());
        while (!file.eof()) {
            std::getline(file, temp);
            lines.push_back(temp);
        }
        file.close();
    }
    void add(string line) {lines.push_back(line);}
    char const *get(int index) {
        if (index >= 0 && index < lines.size()) return lines[index].c_str();
        else return NULL;
    }
    int getSize() {return lines.size();}
    ~Text() {lines.clear();}
private:
    vector<string> lines;
};

#endif
