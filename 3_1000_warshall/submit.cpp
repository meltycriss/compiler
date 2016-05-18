//
// Created by criss on 16-5-18.
//
#ifndef INC_3_1000_WARSHALL_WARSHALL_H
#define INC_3_1000_WARSHALL_WARSHALL_H

#include <vector>

class Warshall{
private:
    typedef std::vector<std::vector<int> > matrix;
    matrix mMatrix;
    matrix mMatrixPlus;

public:
    void init();
    void getClosure();
    void printClosure() const;
};

#endif //INC_3_1000_WARSHALL_WARSHALL_H

#include <iostream>
#include <iomanip>

using namespace std;

void Warshall::init() {
    mMatrix.clear();
    mMatrixPlus.clear();
    int n;
    cin >> n;
    mMatrix.resize(n, vector<int>(n, 0));
    for (vector<vector<int> >::size_type i = 0; i < mMatrix.size(); ++i) {
        for (vector<int>::size_type j = 0; j < mMatrix[i].size(); ++j) {
            cin >> mMatrix[i][j];
        }
    }
}

void Warshall::getClosure() {
    mMatrixPlus = mMatrix;
    for (vector<int>::size_type k = 0; k < mMatrixPlus.size(); ++k) {
        for (vector<vector<int> >::size_type i = 0; i < mMatrixPlus.size(); ++i) {
            for (vector<int>::size_type j = 0; j < mMatrixPlus.size(); ++j) {
                if (mMatrixPlus[i][k] == 1 && mMatrixPlus[k][j] == 1) {
                    mMatrixPlus[i][j] = 1;
                }
            }
        }
    }
}

void Warshall::printClosure() const {
    for (vector<vector<int> >::size_type i = 0; i < mMatrixPlus.size(); ++i) {
        for (vector<int>::size_type j = 0; j < mMatrixPlus.size(); ++j) {
            cout << setw(3) << right << mMatrixPlus[i][j];
        }
        cout<<endl;
    }
}

#include <iostream>

using namespace std;

int main() {
    Warshall warshall;
    warshall.init();
    warshall.getClosure();
    warshall.printClosure();
    return 0;
}
