//
// Created by criss on 16-5-29.
//

#ifndef INC_3_1002_TABLE_TABLE_H
#define INC_3_1002_TABLE_TABLE_H

#include <vector>
#include <string>
#include <map>

class Table{
private:
    typedef std::pair<char,std::string> trans;
    typedef std::vector<std::vector<int> > matrix;

    char mStart;
    std::vector<char> mVecNT;
    std::vector<char> mVecT;
    std::vector<char> mVecAllSymbol;
    std::map<char, std::vector<std::string> > mMapTrans;

    matrix mEqual;
    matrix mLEqual;
    matrix mGEqual;

    matrix add(const matrix&, const matrix&);
    matrix multiply(const matrix&, const matrix&);
    matrix tranpose(const matrix&);
    matrix warshall(const matrix&);

    matrix getFirst() const;
    matrix getLast() const;
    matrix getEqual() const;
    matrix getLEqual() const;
    matrix getGEqual() const;

    void printFormat(const std::string&, const matrix&) const;
public:
    void init();
    void genTable();
    void printTable() const;
};

#endif //INC_3_1002_TABLE_TABLE_H
