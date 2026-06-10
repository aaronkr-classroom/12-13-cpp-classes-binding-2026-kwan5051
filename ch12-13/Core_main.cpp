#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Core.h"
#include "Grad.h"
#include "Vec.h"
#include "Student_info.h"
#include "median.h"

using namespace std;

int main(void) {
	vector<Core*> students;
	Core* record;
	char ch;
	string::size_type maxlen = 0;

	while (cin >> ch) {
		if (cin.eof())break;
		if (ch != 'U' && ch != 'G') {
			//학생 아닌 타입이면 건너뛰기
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		if (ch == 'U')
			record = new Core;
		else if (ch == 'G')
			record = new Grad;
		record->read(cin);

		maxlen = max(maxlen, record->getName().size());
		students.push_back(record);
	}

	sort(students.begin(), students.end(), compare_Core_ptrs);

	for (vector<Core*>::size_type i = 0;
		i != students.size(); i++) {

		if (dynamic_cast<Grad*>(students[i])) {
			cout << "(G) "; //대학원생입니다
		}
		else {
			cout << "(U) ";//대학생입니다
		}
		//함수를 호출하려고 포인터인 students[i]를 역함조
		cout << students[i]->getName()
			<< string(maxlen + 1
				- students[i]->getName().size(), ' ');

		try {
			double final_grade = students[i]->grade();
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade
				<< setprecision(prec) << endl;
		}
		catch (domain_error e) {
			cout << e.what() << endl;
		}
		delete students[i];
	}
	return 0;
}
