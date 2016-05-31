//
// Created by criss on 16-5-31.
//

#ifndef INC_3_1003_SLR_SLR_H
#define INC_3_1003_SLR_SLR_H

#include <vector>
#include <string>
#include <map>

class Slr{
private:
    typedef std::pair<char,std::string> trans;
    typedef std::vector<std::vector<int> > matrix;

    enum {
        ERROR=0,
        LESS=1,
        EQUAL=2,
        GREATER=3
    };

    char mStart;
    std::vector<char> mVecNT;
    std::vector<char> mVecT;
    std::vector<char> mVecAllSymbol;
    std::map<char, std::vector<std::string> > mMapTrans;
    matrix analyzeTable;
    std::string mInput;
    std::vector<std::pair<std::string, std::string> > process;

    int getIdx(char) const;
    char findLhs(const std::string &) const;
    std::vector<std::pair<std::string, std::string> > analyze() const;
public:
    void init();
    void compute();
    void print();
};

#endif //INC_3_1003_SLR_SLR_H
