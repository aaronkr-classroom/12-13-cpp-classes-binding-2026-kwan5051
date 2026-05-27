#include <iostream>
#include "Lis.h"

using namespace std;

int main(void) {
	Lis<int> list;
	list.puch_back(1);
	list.puch_back(2);
	list.puch_back(3); 
	list.puch_back(4);
	
	for (Lis<int>::iterator it = list.begin();
		it != list.end(); ++it) {
		cout << *it << endl;
	}
	cout << endl;
}
