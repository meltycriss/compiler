/*//
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

#endif //INC_3_1000_WARSHALL_WARSHALL_H*/
