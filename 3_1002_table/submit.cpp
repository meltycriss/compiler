//
// Created by criss on 16-5-30.
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

    matrix add(const matrix&, const matrix&) const;
    matrix multiply(const matrix&, const matrix&) const;
    matrix tranpose(const matrix&) const;
    matrix warshall(const matrix&) const;

    int getIdx(char) const;

    matrix getUnit(int) const;
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

#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

Table::matrix Table::add(const matrix &lhs, const matrix &rhs) const{
    matrix res = lhs;
    for (int i = 0; i < lhs.size(); ++i) {
        for (int j = 0; j < lhs[i].size(); ++j) {
            if (lhs[i][j] == 1 || rhs[i][j] == 1) {
                res[i][j] = 1;
            }
            else {
                res[i][j] = 0;
            }
        }
    }
    return res;
}

Table::matrix Table::multiply(const matrix &lhs, const matrix &rhs) const{
    matrix res;
    res.resize(lhs.size(), vector<int>(rhs[0].size(), 0));
    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[i].size(); ++j) {
            for (int k = 0; k < rhs.size(); ++k) {
                if (lhs[i][k] == 1 && rhs[k][j] == 1) {
                    res[i][j] = 1;
                }
            }
        }
    }
    return res;
}

Table::matrix Table::tranpose(const matrix &lhs) const{
    matrix res = lhs;
    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[i].size(); ++j) {
            res[i][j] = lhs[j][i];
        }
    }
    return res;
}

Table::matrix Table::warshall(const matrix &lhs) const{
    matrix res = lhs;
    for (int k = 0; k < res.size(); ++k) {
        for (int i = 0; i < res.size(); ++i) {
            for (int j = 0; j < res[i].size(); ++j) {
                if (res[i][k] == 1 && res[k][j] == 1) {
                    res[i][j] = 1;
                }
            }
        }
    }
    return res;
}

void Table::init() {
    mVecNT.clear();
    mVecT.clear();
    mVecAllSymbol.clear();
    mMapTrans.clear();
    mEqual.clear();
    mLEqual.clear();
    mGEqual.clear();

    cin >> mStart;
    int n;
    cin >> n;
    mVecNT.resize(n);
    for (int i = 0; i < n; ++i) cin >> mVecNT[i];

    cin >> n;
    mVecT.resize(n);
    for (int i = 0; i < n; ++i) cin >> mVecT[i];

    mVecAllSymbol = mVecNT;
    mVecAllSymbol.insert(mVecAllSymbol.end(), mVecT.begin(), mVecT.end());

    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        char c;
        string s;
        cin >> x >> c >> s;
        mMapTrans[c].push_back(s);
    }
}

Table::matrix Table::getFirst() const {
    matrix res;
    res.resize(mVecAllSymbol.size(), vector<int>(mVecAllSymbol.size(), 0));
    for (int i = 0; i < mVecAllSymbol.size(); ++i) {
        char s = mVecAllSymbol[i];
        map<char, vector<string> >::const_iterator mp_it;
        if ((mp_it = mMapTrans.find(s)) != mMapTrans.end()) {
            const vector<string> &vecTrans = mp_it->second;
            for (int j = 0; j < vecTrans.size(); ++j) {
                char t = vecTrans[j][0];
                vector<char>::const_iterator vec_it = find(mVecAllSymbol.begin(), mVecAllSymbol.end(), t);
                int idx = vec_it - mVecAllSymbol.begin();
                res[i][idx] = 1;
            }
        }
    }
    return res;
}

Table::matrix Table::getLast() const {
    matrix res;
    res.resize(mVecAllSymbol.size(), vector<int>(mVecAllSymbol.size(), 0));
    for (int i = 0; i < mVecAllSymbol.size(); ++i) {
        char s = mVecAllSymbol[i];
        map<char, vector<string> >::const_iterator mp_it;
        if ((mp_it = mMapTrans.find(s)) != mMapTrans.end()) {
            const vector<string> &vecTrans = mp_it->second;
            for (int j = 0; j < vecTrans.size(); ++j) {
                char t = vecTrans[j][vecTrans[j].size() - 1];
                vector<char>::const_iterator vec_it = find(mVecAllSymbol.begin(), mVecAllSymbol.end(), t);
                int idx = vec_it - mVecAllSymbol.begin();
                res[i][idx] = 1;
            }
        }
    }
    return res;
}

void Table::printFormat(const std::string &_str, const matrix &_mat) const {
    cout << _str << endl;
    for (int i = 0; i < _mat.size() + 1; ++i) {
        for (int j = 0; j < _mat.size() + 1; ++j) {
            if (i == 0) {
                if (j == 0) cout << setw(3) << right << " ";
                else cout << setw(3) << right << mVecAllSymbol[j - 1];
            }
            else {
                if (j == 0) cout << setw(3) << right << mVecAllSymbol[i - 1];
                else cout << setw(3) << right << _mat[i - 1][j - 1];
            }
        }
        cout << endl;
    }
}

int Table::getIdx(char c) const {
    vector<char>::const_iterator vec_it = find(mVecAllSymbol.begin(), mVecAllSymbol.end(), c);
    int idx = vec_it - mVecAllSymbol.begin();
    return idx;
}

Table::matrix Table::getEqual() const {
    matrix res;
    res.resize(mVecAllSymbol.size(), vector<int>(mVecAllSymbol.size(), 0));
    map<char, vector<string> >::const_iterator it_mp = mMapTrans.begin();
    while (it_mp != mMapTrans.end()) {
        const vector<string> &vecTrans = it_mp->second;
        for (int i = 0; i < vecTrans.size(); ++i) {
            string s = vecTrans[i];
            for (int j = 1; j < s.size(); ++j) {
                char l = s[j-1], r = s[j];
                int il = getIdx(l);
                int ir = getIdx(r);
                res[il][ir] = 1;
            }
        }
        ++it_mp;
    }
    return res;
}

Table::matrix Table::getLEqual() const {
    matrix equal = getEqual();
    matrix firstPlus = getFirst();
    firstPlus = warshall(firstPlus);
    matrix res = multiply(equal, firstPlus);
    return res;
}

Table::matrix Table::getUnit(int n) const {
    matrix res;
    res.resize(n, vector<int>(n,0));
    for(int i=0;i<n;++i) res[i][i]=1;
    return res;
}

Table::matrix Table::getGEqual() const {
    matrix lastPlusTranpose = getLast();
    lastPlusTranpose = warshall(lastPlusTranpose);
    lastPlusTranpose = tranpose(lastPlusTranpose);
    matrix equal = getEqual();
    matrix firstStar = getFirst();
    firstStar = warshall(firstStar);
    matrix unit = getUnit(firstStar.size());
    firstStar = add(unit, firstStar);
    matrix res = multiply(lastPlusTranpose,equal);
    res = multiply(res,firstStar);
    return res;
}


void Table::genTable() {
    mEqual = getEqual();
    mLEqual = getLEqual();
    mGEqual = getGEqual();
}

void Table::printTable() const {
    printFormat("EQUAL=",mEqual);
    printFormat("LEQUAL=",mLEqual);
    printFormat("GEQUAL=",mGEqual);


    cout << "M[R]=" << endl;
    for (int i = 0; i < mVecAllSymbol.size() + 1; ++i) {
        for (int j = 0; j < mVecAllSymbol.size() + 1; ++j) {
            if (i == 0) {
                if (j == 0) cout << setw(3) << right << " ";
                else cout << setw(3) << right << mVecAllSymbol[j - 1];
            }
            else {
                if (j == 0) cout << setw(3) << right << mVecAllSymbol[i - 1];
                else {
                    if(mEqual[i-1][j-1]==1)
                        cout << setw(3) << right << "=";
                    else if(mLEqual[i-1][j-1]==1)
                        cout << setw(3) << right << "<";
                    else if(mGEqual[i-1][j-1]==1)
                        cout << setw(3) << right << ">";
                    else
                        cout << setw(3) << right << " ";
                }
            }
        }
        cout << endl;
    }
}

using namespace std;

int main() {
    Table tb;
    tb.init();
    tb.genTable();
    tb.printTable();
    return 0;
}
