#include "Elimilator.h"
using namespace std;

int main(){
	Eliminator eliminator;
	eliminator.init();
	eliminator.eliminate();
	eliminator.print();

	system("pause");
	return 0;
}