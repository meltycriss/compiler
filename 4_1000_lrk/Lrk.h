//
// Created by criss on 16-6-2.
//

#ifndef INC_4_1000_LRK_LRK_H
#define INC_4_1000_LRK_LRK_H

#endif //INC_4_1000_LRK_LRK_H

#include <vector>
#include <string>
#include <map>

class Lrk{
private:
    typedef std::pair<char,std::string> trans;
    typedef std::vector<std::vector<int> > matrix;

    char mStart;
    std::vector<char> mVecNT;
    std::vector<char> mVecT;
    std::vector<char> mVecAllSymbol;
    std::vector<trans> mVecTrans;
    std::string mInput;
    std::vector<std::vector<std::pair<char,int> > > analyzeTable;
    std::vector<std::pair<std::string, std::string> > process;

    int getIdx(char) const;
    char findLhs(const std::string &) const;
    std::vector<std::pair<std::string, std::string> > analyze() const;

    void printFormat(const std::string &_str, const matrix &_mat) const;
    void printState(int) const;
public:
    void init();
    void compute();
    void print();
};
