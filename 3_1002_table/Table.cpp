//
// Created by criss on 16-5-29.
//

#include "Table.h"
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