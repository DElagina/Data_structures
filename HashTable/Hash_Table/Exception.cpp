#include "Exception.h"
#include <iostream>

using namespace std;

Exception::Exception() {}

Exception::~Exception() {}

Exception::Exception(int &errcode, char *msg)
{
	this->errcode = errcode;
	this->msg = msg;
}

void Exception::Show()
{
	cout << "Îøèáêà ¹" << this->errcode << ": '" << this->msg << "'" << endl;
}
