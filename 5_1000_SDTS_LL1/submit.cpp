//
// Created by criss on 16-6-4.
//
#ifndef INC_2_1001_LL1_LL1_H
#define INC_2_1001_LL1_LL1_H

#include <vector>
#include <string>
#include <map>

class LL1 {
private:
    typedef std::pair<char, std::string> trans;
    char mStart;
    std::vector<char> mVecNT;
    std::vector<char> mVecT;
    std::vector<trans> mVecTrans;
    std::map<std::pair<char, char>, int> mMapAnalyzeTable;
    std::vector<std::pair<std::string, std::string> > mProcess;
    bool mIsAnalyzeOK;
    std::vector<int> mRes;
    std::vector<std::string> mVecOutput;

public:
    void init();

    bool analyze(const std::string &);

    void printAnalyzeTable() const;

    void printAnalyzeProcess() const;

    void printRes() const;
};

#endif //INC_2_1001_LL1_LL1_H

#include <iostream>
#include <iomanip>

using namespace std;

void LL1::init() {
    mVecNT.clear();
    mVecT.clear();
    mVecTrans.clear();
    mMapAnalyzeTable.clear();
    mRes.clear();
    mVecOutput.clear();

    cin >> mStart;
    int n;
    char c;
    string s;
    cin >> n;
    while (n--) {
        cin >> c;
        mVecNT.push_back(c);
    }
    cin >> n;
    while (n--) {
        cin >> c;
        mVecT.push_back(c);
    }
    cin >> n;
    while (n--) {
        int x;
        cin >> x;
    }

    cin >> n;
    while (n--) {
        int temp;
        cin >> temp;
        cin >> c >> s;
        mVecTrans.push_back(make_pair(c, s));
    }

    cin >> n;
    while (n--) {
        int x;
        string s;
        cin >> x >> s;
        mVecOutput.push_back(s);
    }

    cin >> n;
    while (n--) {
        int temp;
        char nt, t;
        int idx;
        cin >> temp;
        cin >> nt >> t >> idx;
        mMapAnalyzeTable[make_pair(nt, t)] = idx;
    }
}

void LL1::printAnalyzeTable() const {
    for (int i = 0; i < mVecNT.size() + 1; ++i) {
        for (int j = 0; j < mVecT.size() + 2; ++j) {
            if (i == 0) {
                if (j == 0) cout << setw(5) << right << " ";
                else if (j == mVecT.size() + 1) cout << setw(5) << right << "#";
                else cout << setw(5) << right << mVecT[j - 1];
            }
            else {
                if (j == 0) cout << setw(5) << right << mVecNT[i - 1];
                else {
                    char nt, t;
                    nt = mVecNT[i - 1];
                    if (j == mVecT.size() + 1) t = '#';
                    else t = mVecT[j - 1];
                    pair<char, char> p = make_pair(nt, t);
                    map<pair<char, char>, int>::const_iterator mp_it;
                    if ((mp_it = mMapAnalyzeTable.find(p)) != mMapAnalyzeTable.end()) {
                        int idx = mp_it->second;
                        string expr = mVecTrans[idx - 1].second;
                        cout << setw(5) << right << expr;
                    }
                    else {
                        cout << setw(5) << right << " ";
                    }
                }

            }
        }
        cout << endl;
    }
}

bool LL1::analyze(const string &_input) {
    mProcess.clear();
    mIsAnalyzeOK = true;
    string::size_type curIdx = 0;
    string curRecog = "";
    string curExpr = " ";
    curExpr[0] = mStart;
    mProcess.push_back(make_pair(curRecog, curExpr));
    while (curIdx < _input.size() && curExpr.size() > 0) {
        char t = _input[curIdx], expr = curExpr[0];
        //modify
        if(expr<='9' && expr>='0'){
            mRes.push_back(expr-'0'-1);
            curExpr = curExpr.substr(1);
        }
        else if (t == expr) {
            ++curIdx;
            curRecog = _input.substr(0, curIdx);
            curExpr = curExpr.substr(1);
        }
        else {
            int idxTrans;
            pair<char, char> p = make_pair(expr, t);
            if (mMapAnalyzeTable.find(p) != mMapAnalyzeTable.end()) {
                idxTrans = mMapAnalyzeTable[p];
            }
                //could not find the corresponding translation
            else {
                mIsAnalyzeOK = false;
                break;
            }
            string trans = mVecTrans[idxTrans - 1].second;
            if (trans == "k") trans = "";
            curExpr = trans + curExpr.substr(1);

        }
        mProcess.push_back(make_pair(curRecog, curExpr));
    }
    if (curIdx != _input.size() - 1 || curExpr.size() != 0) mIsAnalyzeOK = false;
    return mIsAnalyzeOK;
}

void LL1::printAnalyzeProcess() const {
    for (int i = 0; i < mProcess.size(); ++i) {
        cout << "#" << mProcess[i].first << " & " << mProcess[i].second << "#" << endl;
    }
}

void LL1::printRes() const {
    for (int i = 0; i < mRes.size(); ++i) {
        int idx = mRes[i];
        cout<<" "<<mVecOutput[idx];
    }
    cout << endl;
}

#include <iostream>

using namespace std;

int main() {
    LL1 ll1;
    ll1.init();
    //ll1.printAnalyzeTable();
    string s;
    cin >> s;
    ll1.analyze(s);
//    ll1.printAnalyzeProcess();
    ll1.printRes();


    return 0;
}

