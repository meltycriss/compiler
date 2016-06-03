//
// Created by criss on 16-6-3.
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

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

const Lrk::action Lrk::ERROR_ACTION = make_pair('k', 0);
const Lrk::action Lrk::ACCEPT = make_pair('A', 0);
const Lrk::action Lrk::ERROR_GOTO = make_pair('s', 0);


void Lrk::init() {
    mVecNT.clear();
    mVecT.clear();
    mVecAllSymbol.clear();
    mVecTrans.clear();
    analyzeTable.clear();
    mInput.clear();
    process.clear();
    mStack.clear();

    cin >> mStart;

    int n;
    cin >> n;
    mVecNT.resize(n);
    for (int i = 0; i < n; ++i) cin >> mVecNT[i];

    cin >> n;
    mVecT.resize(n);
    for (int i = 0; i < n; ++i) cin >> mVecT[i];

    mVecAllSymbol = mVecT;
    mVecAllSymbol.insert(mVecAllSymbol.end(), mVecNT.begin(), mVecNT.end());

    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        char c;
        string s;
        cin >> x >> c >> s;
        mVecTrans.push_back(make_pair(c, s));
    }

    int nAction, nGoto;
    cin >> n >> nAction >> nGoto;
    analyzeTable.resize(n);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        for (int j = 0; j < nAction; ++j) {
            char c;
            int num;
            cin >> c >> num;
            analyzeTable[i].push_back(make_pair(c, num));
        }
        for (int j = 0; j < nGoto; ++j) {
            char c = 's';
            int num;
            cin >> num;
            analyzeTable[i].push_back(make_pair(c, num));
        }
    }

    cin >> mInput;
}

void Lrk::pushProcess() {
    string lhs = "";
    for (int i = 0; i < mStack.size(); ++i) {
        char c = mStack[i].first;
        int status = mStack[i].second;
        if (status == 0) {
            lhs.push_back('0');
        }
        else {
            lhs.push_back(c);
            stringstream ss;
            ss << status;
            string strStatus = ss.str();
            lhs.append(strStatus);
        }
    }
    string rhs = mInput.substr(mCurrIdx);
    process.push_back(make_pair(lhs, rhs));
}

void Lrk::compute() {
    analyze();
}

int Lrk::getIdx(char c) const {
    vector<char>::const_iterator it = find(mVecAllSymbol.begin(), mVecAllSymbol.end(), c);
    int res = it - mVecAllSymbol.begin();
    return res;
}

void Lrk::shift(int nextState) {
    char v = mInput[mCurrIdx++];
    mStack.push_back(make_pair(v,nextState));
}

void Lrk::reduce(int idx) {
    char lhs = mVecTrans[idx].first;
    string rhs = mVecTrans[idx].second;
//    if(idx==1) cout<<mStack.size()-rhs.size()<<endl;
    mStack.erase(mStack.end()-rhs.size(),mStack.end());
//    if(idx==1) cout<<lhs<<rhs<<mStack.size()<<" "<<rhs.size()<<endl;
    int state = mStack[mStack.size()-1].second;
    int iLhs = getIdx(lhs);
    action to = analyzeTable[state][iLhs];
    int nextState = to.second;
    mStack.push_back(make_pair(lhs,nextState));
}

void Lrk::analyze() {
    mStack.push_back(make_pair('$', 0));
    mCurrIdx = 0;
    pushProcess();
    int state = mStack[mStack.size() - 1].second;
    int iInput = getIdx(mInput[mCurrIdx]);
    action to = analyzeTable[state][iInput];
    while (to != ACCEPT) {
        //ACTION
        if (iInput < mVecT.size()) {
            //error
            if (to == ERROR_ACTION) return;
            char type = to.first;
            int idx = to.second;
            switch (type) {
                case 's': {
                    shift(idx);
                    break;
                }
                case 'r': {
                    reduce(idx);
                    break;
                }
            }
        }
            //GOTO
        else {
            //error
            if (to == ERROR_GOTO) return;
            shift(to.second);
        }
        pushProcess();
        state = mStack[mStack.size() - 1].second;
        iInput = getIdx(mInput[mCurrIdx]);
        to = analyzeTable[state][iInput];
    }
}

void Lrk::printProcess() const {
    for(int i=0;i<process.size();++i){
        cout<<"#"<<process[i].first<<" & "<<process[i].second<<endl;
    }
}

void Lrk::print() {
    printProcess();
}

using namespace std;

int main() {
    Lrk lrk;
    lrk.init();
    lrk.compute();
    lrk.print();
    return 0;
}
