#pragma once
#include"stack"


class ParserProgram
{
public:
	ParserProgram();
	void action(int i, char *&a, char &how, int &num, char &A, int &b);
	int go_to(int t,char A);
	void error(int i, int j, char *&a);
	~ParserProgram();


};

