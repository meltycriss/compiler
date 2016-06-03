//
// Created by criss on 16-6-2.
//

#ifndef INC_4_1000_LRK_LRK_H
#define INC_4_1000_LRK_LRK_H

#include <vector>
#include <string>
#include <map>

class Lrk{
private:
    typedef std::pair<char,std::string> trans;
    typedef std::vector<std::vector<int> > matrix;
    typedef std::pair<char, int> stackItem;
    typedef std::pair<char, int> action;

    const static action ERROR_ACTION;
    const static action ACCEPT;
    const static action ERROR_GOTO;

    char mStart;
    std::vector<char> mVecNT;
    std::vector<char> mVecT;
    std::vector<char> mVecAllSymbol;
    std::vector<trans> mVecTrans;
    std::string mInput;
    std::vector<std::vector<action> > analyzeTable;
    std::vector<std::pair<std::string, std::string> > process;
    std::vector<stackItem> mStack;
    int mCurrIdx;

    int getIdx(char) const;
    char findLhs(const std::string &) const;
    void analyze();
    void pushProcess();
    void shift(int);
    void reduce(int);

    void printFormat(const std::string &_str, const matrix &_mat) const;
    void printState(int) const;
    void printProcess() const;
public:
    void init();
    void compute();
    void print();
};

#endif //INC_4_1000_LRK_LRK_H

