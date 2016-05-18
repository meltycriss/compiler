#include "eNDFA.h"
#include <iostream>

using namespace std;

int main(){
	eNDFA endfa;
	endfa.init();
	endfa.toDFA();
	endfa.print();
	system("pause");
	return 0;
}