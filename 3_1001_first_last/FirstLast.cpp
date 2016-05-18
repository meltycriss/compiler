//
// Created by criss on 16-5-18.
//
#include "FIrstLast.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

void FirstLast::init() {
    mVecNT.clear();
    mVecT.clear();
    mVecAllSymbol.clear();
    mMapTrans.clear();
    mFirst.clear();
    mFirstPlus.clear();
    mLast.clear();
    mLastPlus.clear();

    cin >> mStart;
    int n;
    cin >> n;
    mVecNT.resize(n);
    for (int i = 0; i < n; ++i) cin >> mVecNT[i];

    cin >> n;
    mVecT.resize(n);
    for (int i = 0; i < n; ++i) cin >> mVecT[i];

    cin >> n;
    for (int i = 0; i < n; ++i) {
        char c;
        string s;
        int x;
        cin >> x >> c >> s;
        mMapTrans[c].push_back(s);
    }

    mVecAllSymbol.insert(mVecAllSymbol.end(), mVecNT.begin(), mVecNT.end());
    mVecAllSymbol.insert(mVecAllSymbol.end(), mVecT.begin(), mVecT.end());
}

FirstLast::matrix FirstLast::warshall(const matrix &_mat) {
    matrix res = _mat;
    for (int k = 0; k < res.size(); ++k) {
        for (int i = 0; i < res.size(); ++i) {
            for (int j = 0; j < res.size(); ++j) {
                if (res[i][k] == 1 && res[k][j] == 1) {
                    res[i][j] = 1;
                }
            }
        }
    }
    return res;
}

void FirstLast::getFirst() {
    mFirst.resize(mVecAllSymbol.size(), vector<int>(mVecAllSymbol.size(), 0));
    for (int i = 0; i < mVecAllSymbol.size(); ++i) {
        char s = mVecAllSymbol[i];
        map<char, vector<string> >::iterator mp_it;
        if ((mp_it = mMapTrans.find(s)) != mMapTrans.end()) {
            const vector<string> &vecTrans = mp_it->second;
            for (int j = 0; j < vecTrans.size(); ++j) {
                char t = vecTrans[j][0];
                vector<char>::iterator vec_it = find(mVecAllSymbol.begin(), mVecAllSymbol.end(), t);
                int idx = vec_it - mVecAllSymbol.begin();
                mFirst[i][idx] = 1;
            }
        }
    }
    mFirstPlus = warshall(mFirst);
}

void FirstLast::getLast() {
    mLast.resize(mVecAllSymbol.size(), vector<int>(mVecAllSymbol.size(), 0));
    for (int i = 0; i < mVecAllSymbol.size(); ++i) {
        char s = mVecAllSymbol[i];
        map<char, vector<string> >::iterator mp_it;
        if ((mp_it = mMapTrans.find(s)) != mMapTrans.end()) {
            const vector<string> &vecTrans = mp_it->second;
            for (int j = 0; j < vecTrans.size(); ++j) {
                char t = vecTrans[j][vecTrans[j].size()-1];
                vector<char>::iterator vec_it = find(mVecAllSymbol.begin(), mVecAllSymbol.end(), t);
                int idx = vec_it - mVecAllSymbol.begin();
                mLast[i][idx] = 1;
            }
        }
    }
    mLastPlus = warshall(mLast);
}

void FirstLast::printFormat(const std::string & _str, const matrix& _mat) const{
    cout<<_str<<endl;
    for(int i=0;i<_mat.size()+1;++i){
        for(int j=0;j<_mat.size()+1;++j){
            if(i==0){
                if(j==0) cout<<setw(3)<<right<<" ";
                else cout<<setw(3)<<right<<mVecAllSymbol[j-1];
            }
            else{
                if(j==0) cout<<setw(3)<<right<<mVecAllSymbol[i-1];
                else cout<<setw(3)<<right<<_mat[i-1][j-1];
            }
        }
        cout<<endl;
    }
}

void FirstLast::printFirstLast() const {
    printFormat("FIRST=",mFirst);
    printFormat("LAST=",mLast);
    printFormat("FIRST+=",mFirstPlus);
    printFormat("LAST+=",mLastPlus);
}
