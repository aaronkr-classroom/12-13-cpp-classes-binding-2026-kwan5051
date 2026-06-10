#include <algorithm>
#include <vector>
#include "Grad.h"

istream& Grad::read(istream& in) {
	Core::read_common(in);
	in >> thesis;
	read_hw(in, homework);
	return in;
}

double Grad::grade()const {
	return min(Core::grade(), thesis);
}
