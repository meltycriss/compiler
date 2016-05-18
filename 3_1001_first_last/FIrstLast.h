//
// Created by criss on 16-5-18.
//

#ifndef INC_3_1001_FIRST_LAST_FIRSTLAST_H
#define INC_3_1001_FIRST_LAST_FIRSTLAST_H

#include <vector>
#include <string>
#include <map>

class FirstLast{
private:
    typedef std::pair<char,std::string> trans;
    typedef std::vector<std::vector<int> > matrix;
    char mStart;
    std::vector<char> mVecNT;
    std::vector<char> mVecT;
    std::vector<char> mVecAllSymbol;
    std::map<char, std::vector<std::string> > mMapTrans;
    matrix mFirst;
    matrix mFirstPlus;
    matrix mLast;
    matrix mLastPlus;
    matrix warshall(const matrix&);
    void printFormat(const std::string&, const matrix&) const;
public:
    void init();
    void getFirst();
    void getLast();
    void printFirstLast() const;
};

#endif //INC_3_1001_FIRST_LAST_FIRSTLAST_H
