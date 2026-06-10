#pragma once
#ifndef GUARD_Grad_h
#define GUARD_Grad_h

#include <iostream>

using namespace std;

class Grad : public Core {
public:
	Grad(): thesis(0){}
	Grad(istream& is) {read(is);}
	double grade()const;
	istream& read(istream&);

private:
	double thesis;
	Grad* clone() const { return new Grad(*this); }
};
#endif // !GUARD_Grad_H
