#pragma once

class Exception
{
public:
	Exception();
	Exception(int &errcode, char *msg);
	~Exception();
	virtual void Show();
private:
	char *msg;
	int errcode;
};