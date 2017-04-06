// Parser.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include"stack"
#include"iostream"
#include"ParserProgram.h"
using namespace std;

//����ջ
static stack<char> symbol;
//״̬ջ
static stack<int> state;
static char sen[50];
static char sym[12][6] = { { 's','e','e','s','e','e' },           //���ű�
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

static char snum[12][6] = {//���ֱ�
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

static int go_to_[12][3] = {//goto��
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
int main()
{

	ParserProgram pp;
	int s;
	char *a;
	char how;
	int num;
	int b;
	char A;
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
			pp.action(s, a, how, num, A, b);	
			if (how == 's')
			{
				cout << "�ƽ�" << endl;
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
				state.push(pp.go_to(t, A));
			}
			else if (how == 'a')
			{
				break;
			}
			else
			{
				pp.error(s, num, a);
			}
		}
		cout << "�ɹ�����" << endl;
	}
    return 0;
}

