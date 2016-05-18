#include "Lexer.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
	Lexer lexer;
	lexer.init();
	lexer.lexicalAnalyze();
	lexer.print();
	system("pause");
	return 0;
}