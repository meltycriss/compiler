/*//
// Created by criss on 16-5-16.
//

#ifndef INC_2_1001_LL1_LL1_H
#define INC_2_1001_LL1_LL1_H

#include <vector>
#include <string>
#include <map>

class LL1{
private:
    typedef std::pair<char, std::string> trans;
    char mStart;
    std::vector<char> mVecNT;
    std::vector<char> mVecT;
    std::vector<trans> mVecTrans;
    std::map<std::pair<char, char>, int> mMapAnalyzeTable;
    std::vector<std::pair<std::string,std::string> > mProcess;
    bool mIsAnalyzeOK;

public:
    void init();
    bool analyze(const std::string&);
    void printAnalyzeTable() const;
    void printAnalyzeProcess() const;
};

#endif //INC_2_1001_LL1_LL1_H*/
