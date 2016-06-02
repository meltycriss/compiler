//
// Created by criss on 16-6-2.
//

#include "Lrk.h"
#include <iostream>

using namespace std;

void Lrk::init(){
    mVecNT.clear();
    mVecT.clear();
    mVecAllSymbol.clear();
    mVecTrans.clear();
    analyzeTable.clear();
    mInput.clear();
    process.clear();

    cin>>mStart;

    int n;
    cin>>n;
    mVecNT.resize(n);
    for(int i=0;i<n;++i) cin>>mVecNT[i];

    cin>>n;
    mVecT.resize(n);
    for(int i=0;i<n;++i) cin>>mVecT[i];

    mVecAllSymbol = mVecNT;
    mVecAllSymbol.insert(mVecAllSymbol.end(),mVecT.begin(),mVecT.end());

    cin>>n;
    for(int i=0;i<n;++i){
        int x;
        char c;
        string s;
        cin>>x>>c>>s;
        mVecTrans.push_back(make_pair(c,s));
    }

    int nAction, nGoto;
    cin>>n>>nAction>>nGoto;
    analyzeTable.resize(n);
    for(int i=0;i<n;++i){
        int x;
        cin>>x;
        for(int j=0;j<nAction;++j){
            char c;
            int num;
            cin>>c>>num;
            analyzeTable[i].push_back(make_pair(c,num));
        }
        for(int j=0;j<nGoto;++j){
            char c = 's';
            int num;
            cin>>num;
            analyzeTable[i].push_back(make_pair(c,num));
        }
    }

    cin>>mInput;
}
