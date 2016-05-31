//
// Created by criss on 16-5-31.
//

#include "Slr.h"
#include <iostream>
#include <algorithm>

using namespace std;

void Slr::init() {
    mVecNT.clear();
    mVecT.clear();
    mVecAllSymbol.clear();
    mMapTrans.clear();
    analyzeTable.clear();
    process.clear();

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

    cin >> n;
    analyzeTable.resize(mVecAllSymbol.size(), vector<int>(mVecAllSymbol.size(), 0));
    n = mVecAllSymbol.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> analyzeTable[i][j];
        }
    }

    cin >> mInput;
    mInput.erase(mInput.size()-1);
}

int Slr::getIdx(char c) const {
    vector<char>::const_iterator it = find(mVecAllSymbol.begin(), mVecAllSymbol.end(), c);
    int idx = it - mVecAllSymbol.begin();
    return idx;
}

char Slr::findLhs(const std::string &rhs) const {
    char res;
    bool hasFound = false;
    map<char,vector<string> >::const_iterator it_mp = mMapTrans.begin();
    while(it_mp!=mMapTrans.end()){
        const vector<string> &vecTrans = it_mp->second;
        for(int i=0;i<vecTrans.size();++i){
            if(rhs == vecTrans[i]){
                res = it_mp->first;
                hasFound = true;
                break;
            }
        }
        if(hasFound) break;
        ++it_mp;
    }
    return res;
}

vector<pair<string, string> > Slr::analyze() const {
    vector<pair<string, string> > res;
    string strStack = "";
    int currIdx = 0;
    string strCurrInput = mInput.substr(currIdx);
    res.push_back(make_pair(strStack, strCurrInput));
    while (!(strStack.size() == 1 && strStack[0] == mStart && strCurrInput.size() == 0)) {
        if (strStack.size() == 0) {
            //error
            if (strCurrInput.size() == 0) return res;
            else {
                strStack.push_back(strCurrInput[0]);
                ++currIdx;
                strCurrInput = mInput.substr(currIdx);
            }
        }
        else {
            char cStack = strStack[strStack.size() - 1];
            char cInput = strCurrInput[0];
            int iStack = getIdx(cStack);
            int iInput = getIdx(cInput);
            if (strCurrInput.size() == 0) {
                //same to GREATER
                int idx = strStack.size() - 2;
                //error
                if (idx < 0) return res;
                cStack = strStack[idx];
                iStack = getIdx(cStack);
                while(analyzeTable[iStack][iInput]!=LESS) {
                    //error
                    if(analyzeTable[iStack][iInput]!=EQUAL) return res;
                    --idx;
                    //error
                    if (idx < 0) return res;
                    cStack = strStack[idx];
                    iStack = getIdx(cStack);
                }
                string rhs = strStack.substr(idx);
                char lhs = findLhs(rhs);
                strStack.erase(idx);
                strStack.push_back(lhs);
            }
            else {
                switch (analyzeTable[iStack][iInput]) {
                    case LESS: {
                        strStack.push_back(strCurrInput[0]);
                        ++currIdx;
                        strCurrInput = mInput.substr(currIdx);
                        break;
                    }
                    case EQUAL: {
                        strStack.push_back(strCurrInput[0]);
                        ++currIdx;
                        strCurrInput = mInput.substr(currIdx);
                        break;
                    }
                    case GREATER: {
                        int idx = strStack.size() - 2;
                        //error
                        if (idx < 0) return res;
                        cStack = strStack[idx];
                        iStack = getIdx(cStack);
                        while(analyzeTable[iStack][iInput]!=LESS) {
                            //error
                            if(analyzeTable[iStack][iInput]!=EQUAL) return res;
                            --idx;
                            //error
                            if (idx < 0) return res;
                            cStack = strStack[idx];
                            iStack = getIdx(cStack);
                        }
                        string rhs = strStack.substr(idx);
                        char lhs = findLhs(rhs);
                        strStack.erase(idx);
                        strStack.push_back(lhs);
                        break;
                    }
                    //error
                    default:
                        return res;
                }
            }
        }
        res.push_back(make_pair(strStack,strCurrInput));
    }
    return res;
}

void Slr::compute() {
    process = analyze();
}

void Slr::print() {
    for(int i=0;i<process.size();++i){
        cout<<"#" << process[i].first<< " & " << process[i].second<< "#" << endl;
    }
}

