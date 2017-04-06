// Parser.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"stack"
#include"iostream"
#include"ParserProgram.h"
using namespace std;

void action(int i, char *&a, char &how, int &num, char &A, int &b, char sym[][6], char snum[][6])
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
	if (j != -1)
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

int go_to(int t, char A, int go_to[][3])
{
	switch (A)
	{
	case 'E':
		return go_to[t][0];
		break;
	case 'T':
		return go_to[t][1];
		break;
	case 'F':
		return go_to[t][2];
		break;
	}
}


void error(int i, int j, char *& a, stack<int> state, stack<char> symbol)
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

int main()
{
	//符号栈
	static stack<char> symbol;
	//状态栈
	static stack<int> state;
	static char sen[50];
	static char sym[12][6] = { { 's','e','e','s','e','e' },           //符号表
	{ 'e','s','e','e','e','a' },
	{ 'r','r','s','r','r','r' },
	{ 'r','r','r','r','r','r' },
	{ 's','e','e','s','e','e' },
	{ 'r','r','r','r','r','r' },
	{ 's','e','e','s','e','e' },
	{ 's','e','e','s','e','e' },
	{ 'e','s','e','e','s','e' },
	{ 'r','r','s','r','r','r' },
	{ 'r','r','r','r','r','r' },
	{ 'r','r','r','r','r','r' } };

	static char snum[12][6] = {//数字表
		{ 5,1,1,4,2,1 },
		{ 3,6,5,3,2,0 },
		{ 2,2,7,2,2,2 },
		{ 4,4,4,4,4,4 },
		{ 5,1,1,4,2,1 },
		{ 6,6,6,6,6,6 },
		{ 5,1,1,4,2,1 },
		{ 5,1,1,4,2,1 },
		{ 3,6,5,3,11,4 },
		{ 1,1,7,1,1,1 },
		{ 3,3,3,3,3,3 },
		{ 5,5,5,5,5,5 } };

	static int go_to_[12][3] = {//goto表
		{ 1,2,3 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 8,2,3 },
		{ 0,0,0 },
		{ 0,9,3 },
		{ 0,0,10 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 } };

	//ParserProgram pp;
	int s;
	char *a;
	char how;
	int num;
	int b;
	char A;
	//char(*sym_) = &sym[0][0];
	//char(*snum_) = &snum[0][0];
	while (true)
	{
		cin >> sen;
		a = sen;
		state.push(0);
		while (*a != '\0')
		{
			b = 0;
			num = 0;
			how = '\0';
			A = '\0';
			s = state.top();
			action(s, a, how, num, A, b,sym,snum);	
			if (how == 's')
			{
				cout << "移进" << endl;
				symbol.push(*a);
				state.push(num);
				a++;
			}
			else if (how == 'r')
			{
				for (int i = 0; i < b; i++)
				{
					if (!state.empty())
					{
						state.pop();
					}
					if (!symbol.empty())
					{
						symbol.pop();
					}
				}
				int t = state.top();	
				symbol.push(A);
				state.push(go_to(t, A,go_to_));
			}
			else if (how == 'a')
			{
				break;
			}
			else
			{
				error(s,num,a,state,symbol);
			}
		}
		cout << "成功接收" << endl;
	}
    return 0;
}



