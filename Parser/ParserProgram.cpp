#include "stdafx.h"
#include "ParserProgram.h"
#include"iostream"


using namespace std;


ParserProgram::ParserProgram()
{
	cout << "program is preparing.." << endl;
}

void ParserProgram::action(int i, char *&a, char &how, int &num, char &A, int &b)
{
	int j;
	switch (*a)
	{
	case'i':j = 0; break;
	case'+':j = 1; break;
	case'*':j = 2; break;
	case'(':j = 3; break;
	case')':j = 4; break;
	case'#':j = 5; break;
	default:j = -1; break;
	}
	if (j!=-1)
	{
		how = sym[i][j];
		num = snum[i][j];
		if (how == 'r')
		{
			switch (num)
			{
			case 1:A = 'E';
				b = 3;
				cout << "按E->E+T规约" << endl;
				break;
			case 2:A = 'E';
				b = 1;
				cout << "按E->T规约" << endl;
				break;
			case 3:A = 'T';
				b = 3;
				cout << "按T->T*F规约" << endl;
				break;
			case 4:A = 'T';
				b = 1;
				cout << "按T->F规约" << endl;
				break;
			case 5:A = 'F';
				b = 3;
				cout << "按F->(E)规约" << endl;
				break;
			case 6:A = 'F';
				b = 1;
				cout << "按F->i规约" << endl;
				break;
			default:
				break;
			}
		}
	}
}

int ParserProgram::go_to(int t, char A)
{
	switch (A)
	{
	case 'E':
		return go_to_[t][0];
		break;
	case 'T':
		return go_to_[t][1];
		break;
	case 'F':
		return go_to_[t][2];
		break;
	}
}


void ParserProgram::error(int i, int j, char *& a)
{
	cout << "error.." << endl;
	switch (j)
	{
	case 1:
		state.push(5);
		symbol.push('i');
		cout << "缺少运算对象i" << endl;
		break;
	case 2:
		a++;
		cout << "不配对的右括号" << endl;
		break;
	case 3:
		state.push(6);
		symbol.push('+');
		cout << "缺少运算符" << endl;
		break;
	case 4:
		state.push(11);
		symbol.push(')');
		cout << "缺少右括号" << endl;
		break;
	case 5:
		a++;
		cout << "*号无效，请换成+号再试一次" << endl;
	case '6':
		a++;
	default:
		break;
	}
}

ParserProgram::~ParserProgram()
{
	cout << "ending of program.." << endl;
}
