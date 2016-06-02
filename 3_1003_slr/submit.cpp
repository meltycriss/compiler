//
// Created by criss on 16-6-2.
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

    void printFormat(const std::string &_str, const matrix &_mat) const;
    void printState(int) const;
public:
    void init();
    void compute();
    void print();
};

#endif //INC_3_1003_SLR_SLR_H

#include <iostream>
#include <algorithm>
#include <iomanip>

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
    mInput.erase(mInput.size() - 1);

/*    //debug
    printFormat("table", analyzeTable);*/

}

int Slr::getIdx(char c) const {
    vector<char>::const_iterator it = find(mVecAllSymbol.begin(), mVecAllSymbol.end(), c);
    int idx = it - mVecAllSymbol.begin();
    return idx;
}

char Slr::findLhs(const std::string &rhs) const {
    char res;
    bool hasFound = false;
    map<char, vector<string> >::const_iterator it_mp = mMapTrans.begin();
    while (it_mp != mMapTrans.end()) {
        const vector<string> &vecTrans = it_mp->second;
        for (int i = 0; i < vecTrans.size(); ++i) {
            if (rhs == vecTrans[i]) {
                res = it_mp->first;
                hasFound = true;
                break;
            }
        }
        if (hasFound) break;
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
                //if (idx < 0) return res;
                char prevCharStack;
                int prevIntStack;
                if (idx >= 0) {
                    prevCharStack = strStack[idx];
                    prevIntStack = getIdx(prevCharStack);
                }
/*                cout << "prev: " << prevCharStack << " " << cStack << endl;*/
                while (idx >= 0 && analyzeTable[prevIntStack][iStack] != LESS) {
                    //error
                    if (analyzeTable[prevIntStack][iStack] != EQUAL) return res;
                    --idx;
                    //error
                    if (idx >= 0) {
                        iStack = prevIntStack;
                        prevCharStack = strStack[idx];
                        prevIntStack = getIdx(prevCharStack);
                    }
                }
                ++idx;
                string rhs = strStack.substr(idx);
                char lhs = findLhs(rhs);
                strStack.erase(idx);
                strStack.push_back(lhs);
/*                cout << strStack << endl;*/
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
                        //if (idx < 0) return res;
                        char prevCharStack;
                        int prevIntStack;
                        if (idx >= 0) {
                            prevCharStack = strStack[idx];
                            prevIntStack = getIdx(prevCharStack);
                        }
/*                        cout << "prev: " << prevCharStack << " " << cStack << endl;*/
                        while (idx >= 0 && analyzeTable[prevIntStack][iStack] != LESS) {
                            //error
                            if (analyzeTable[prevIntStack][iStack] != EQUAL) return res;
                            --idx;
                            //error
                            if (idx >= 0) {
                                iStack = prevIntStack;
                                prevCharStack = strStack[idx];
                                prevIntStack = getIdx(prevCharStack);
                            }
                        }
                        ++idx;
                        string rhs = strStack.substr(idx);
                        char lhs = findLhs(rhs);
                        strStack.erase(idx);
                        strStack.push_back(lhs);
/*                        cout << strStack << endl;*/
                        break;
                    }
                        //error
                    default:
                        return res;
                }
            }
        }
        res.push_back(make_pair(strStack, strCurrInput));
    }
    return res;
}

void Slr::compute() {
    process = analyze();
}

void Slr::print() {
    for (int i = 0; i < process.size(); ++i) {
        cout << "#" << process[i].first << " & " << process[i].second << "#" << endl;
    }
}

void Slr::printFormat(const std::string &_str, const matrix &_mat) const {
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

void Slr::printState(int _state) const {
    switch (_state) {
        case ERROR:
            cout << "ERROR" << endl;
            break;
        case LESS:
            cout << "LESS" << endl;
            break;
        case EQUAL:
            cout << "EQUAL" << endl;
            break;
        case GREATER:
            cout << "GREATER" << endl;
            break;
    }
}

using namespace std;

int main() {
    Slr slr;
    slr.init();
    slr.compute();
    slr.print();
    return 0;
}
